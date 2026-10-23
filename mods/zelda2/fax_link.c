/* Faxanadu world adapter. Original ROM code owns scripts, item/door checks,
 * damage formulae, enemy defeats and transitions. No PRG image is patched. */
#include "fax_link.h"
#include "fax_profile.h"
#include "cyc_mod.h"
#include "cyc_core.h"
#include "cyc_render.h"
#include "mod_runtime.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "mod_audio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef CYC_WITH_SDL
#include "cyc_tcp.h"
#include <SDL.h>
#endif

FaxLinkState fax_link;
static int enabled;
static uint32_t picture[256*240],frozen[256*240];
static ForeignMoveResult move;
#define raw_pad fax_link.raw_buttons
#define raw_changed fax_link.raw_changed
static int cast_key=6,picker_key=25; /* SDL scancodes C and V; 0 disables */
#define R(n) cyc_mod_peek(F_##n)
#define W(n,v) cyc_mod_poke(F_##n,(uint8_t)(v))
#define Q(a) cyc_mod_peek((uint16_t)(a))
#define P(a,v) cyc_mod_poke((uint16_t)(a),(uint8_t)(v))
#define S fax_link
static int guest(uint16_t addr,int a,int x,int y) {
    CycModRegs r;cyc_mod_regs(&r);r.a=(uint8_t)a;r.x=(uint8_t)x;r.y=(uint8_t)y;
    if(!cyc_mod_call_commit_hooked(addr,&r)) {
        fprintf(stderr,"[Link] native helper $%04x failed; refusing partial gameplay\n",addr);abort();
    }
    return r.a;
}
/* Schedule a native tail call through the hook's documented handled-RTS.
 * Push target-1 ABOVE the untouched caller return. The scheduler pops this
 * pair, then the native routine executes normally, including mapper/device
 * writes, and its RTS returns to the original caller. No unclocked I/O. */
static int tail(uint16_t addr,int x) {
    CycModRegs r;cyc_mod_regs(&r);uint16_t ret=addr-1;
    P(0x100|r.s,ret>>8);--r.s;P(0x100|r.s,ret);--r.s;
    r.x=(uint8_t)x;cyc_mod_set_regs(&r);return 1;
}
static int category(int slot) {
    unsigned id=Q(F_CurrentSprites_Entities+slot);
    return id<0x42?Q(F_SPRITE_CATEGORIES_BY_ENTITY+id):-1;
}
static int enemy(int slot) {
    int c=category(slot);
    return (c==0||c==7)&&!(Q(F_CurrentSprites_Flags+slot)&0x10);
}
static int overlap(int ax,int ay,int aw,int ah,int bx,int by,int bw,int bh) {
    return ax<bx+bw&&bx<ax+aw&&ay<by+bh&&by<ay+ah;
}
static int prop_at(int x,int y) {
    unsigned tile;
    if(x<0)tile=Q(F_LastColumnLeftScreen+((y&255)>>4));
    else if(x>=256)tile=Q(F_FirstColumnInRightScreen+((y&255)>>4));
    else if(y<0)tile=Q(F_LastRowAboveScreen+(x>>4));
    else if(y>=208)tile=Q(F_FirstRowBelowScreen+(x>>4));
    else tile=Q(F_ScreenBuffer+(y&0xf0)+(x>>4));
    unsigned packed=Q(F_BlockProperties+(tile>>1));
    return tile&1?packed>>4:packed&15;
}
static int solid(int x,int y) {return Q(F_BLOCK_PROPERTY_IMPASSABLE_MAP+prop_at(x,y))!=0;}
static int blocked(int x,int y,int fairy,int crouch) {
    /* Crouch changes the hurtbox; it cannot crawl into a passage from which
     * Zelda II's stationary crouch has no way to retreat. Fairy can fly out. */
    (void)crouch;
    int left=x+(fairy?4:0),top=y+(fairy?12:0);
    int width=fairy?8:16,height=fairy?8:32;
    for(int yy=top;yy<top+height;yy+=height-1)
        for(int xx=left;xx<left+width;xx+=width-1)if(solid(xx,yy))return 1;
    /* Middle row prevents crossing a tile omitted by the corner samples. */
    return height>16&&(solid(left,top+16)||solid(left+width-1,top+16));
}
static void clear_scene(void) {
    S.effects=0;S.transformed=0;S.thunder=0;S.fairy_pending_end=0;
    memset(S.projectile,0,sizeof S.projectile);
}
static void reseed(void) {
    nes_foreign_select(LINK_CONTROLLER_ID);
    ForeignState *s=nes_foreign_state();s->x=R(Player_PosX_Block)+R(Player_PosX_Frac)/256.0;
    s->y=R(Player_PosY);s->grounded=!blocked((int)s->x,(int)s->y+1,0,0)?0:1;
    s->facing=R(Player_Flags)&0x40?1:-1;
    LinkPrivate p=*link_private();p.motion_direction=s->facing>0?1:2;link_restore(s,&p);
}
static void sync_scene(void) {
    if(!S.initialized||S.area!=R(Area_CurrentArea)||S.screen!=R(Area_CurrentScreen)) {
        int fairy=S.effects&(1u<<LINK_FAIRY_SPELL);
        clear_scene();reseed();S.initialized=1;S.area=R(Area_CurrentArea);S.screen=R(Area_CurrentScreen);
        if(fairy&&blocked(R(Player_PosX_Block),R(Player_PosY),0,0)) {
            S.effects|=1u<<LINK_FAIRY_SPELL;S.fairy_pending_end=1;
        }
    }
    if(S.fairy_pending_end&&!blocked(R(Player_PosX_Block),R(Player_PosY),0,0)) {
        S.effects&=(uint8_t)~(1u<<LINK_FAIRY_SPELL);S.fairy_pending_end=0;reseed();
    }
}
static void advance_projectiles(void) {
    for(int i=0;i<LINK_PROJECTILES;i++) {
        LinkProjectile *p=&S.projectile[i];if(!p->life)continue;
        --p->life;int dir=p->vx>0?1:-1;
        for(int step=0;step<abs(p->vx)/256&&p->life;step++) {
            p->x+=dir*256;int x=p->x/256,y=p->y/256;
            if(x<0||x>255||y<0||y>207||solid(x,y)||solid(x+7,y+7))p->life=0;
        }
    }
}
static void spawn(unsigned kind,int x,int y,int dir) {
    for(int i=0;i<LINK_PROJECTILES;i++)if(!S.projectile[i].life) {
        S.projectile[i]=(LinkProjectile){x*256,y*256,dir*512,kind==LINK_BEAM?32:128,(uint8_t)(kind==LINK_BEAM?1:2),0};
        fax_link_audio_cue(kind==LINK_BEAM?2:3);break;
    }
}
static int can_cast(unsigned spell) {
    if(spell>=8||R(Player_MP)<link_spell_cost(spell,80))return 0;
    if((spell==LINK_LIFE&&R(Player_HP_U)>=80)||
       ((spell==LINK_SHIELD||spell==LINK_JUMP||spell==LINK_FAIRY_SPELL||spell==LINK_FIRE||spell==LINK_REFLECT)&&
       (S.effects&(1u<<spell))))return 0;
    return 1;
}
static void cast(void) {
    if(!can_cast(S.spell)){fax_link_audio_cue(4);return;}
    unsigned cost=link_spell_cost(S.spell,80);
    /* HUD helpers only enqueue RAM packets. The actual PPU work remains native. */
    guest(F_Player_SetMP,R(Player_MP)-cost,0,0);
    if(S.spell==LINK_LIFE)guest(F_Player_AddHP,15,0,0); /* $30 / $100 of 80 HP */
    else if(S.spell==LINK_SPELL) {
        for(int i=0;i<8;i++)if(enemy(i)&&category(i)==0) {
            unsigned id=Q(F_CurrentSprites_Entities+i);
            if(id!=0x11&&(id<0x2d||id>0x33))S.transformed|=(uint8_t)(1u<<i);
        }
    } else if(S.spell==LINK_THUNDER){
        S.thunder=0;for(int i=0;i<8;i++)if(enemy(i))S.thunder|=(uint8_t)(1u<<i);
        S.flash=8;
    }
    else S.effects|=(uint8_t)(1u<<S.spell);
    fax_link_audio_cue(3);
}
static void native_ownership(void) {
    S.foreign=0;nes_foreign_set_ownership(FOREIGN_OWNERSHIP_SCRIPTED);
    ForeignState *s=nes_foreign_state();if(!s)return;
    s->x=R(Player_PosX_Block)+R(Player_PosX_Frac)/256.0;s->y=R(Player_PosY);
    s->vx=s->vy=0;s->grounded=!(R(Player_Flags)&5);
    ForeignInput input={0};ForeignMoveResult ignored;input.raw_buttons=raw_pad;
    nes_foreign_tick(++S.ticks,&input,&ignored);
}
static int player_hook(uint16_t addr) {
    (void)addr;CycModRegs r;cyc_mod_regs(&r);
    unsigned caller=Q(0x100|(uint8_t)(r.s+1))|(Q(0x100|(uint8_t)(r.s+2))<<8);
    int ordinary=caller>=F_Game_MainLoop&&caller<F_EndGame_MainLoop;
    if(!ordinary||R(PlayerIsDead)||!(R(IScript_PortraitID)&0x80)) {
        raw_pad=raw_changed=0;
        native_ownership();return 0;
    }
    raw_pad=R(Joy1_ButtonMask);raw_changed=R(Joy1_ChangedButtonMask);
    int was_picker=S.picker;
    if((raw_changed&0x20)||S.shortcut_picker) {
        if(!S.picker){
            memcpy(frozen,cyc_frame_argb(),sizeof frozen);
            S.draw=S.previous_draw;fax_link_render(frozen);S.draw=0;
            S.cursor=S.spell;S.picker=1;
        }
        else S.picker=0;
        S.shortcut_picker=0;
    } else if(S.picker) {
        if(raw_changed&0x0a)S.cursor=(S.cursor+7)&7;
        if(raw_changed&0x05)S.cursor=(S.cursor+1)&7;
        if(raw_changed&0x80){S.spell=S.cursor;S.picker=0;}
        if(raw_changed&0x40)S.picker=0;
        W(Joy1_ButtonMask,0);W(Joy1_ChangedButtonMask,0);
    }
    if(S.picker) {S.foreign=0;return tail(F_Game_MainLoop,0);}
    if(was_picker){raw_pad=raw_changed=0;W(Joy1_ButtonMask,0);W(Joy1_ChangedButtonMask,0);}
    if(R(Screen_ScrollDirection)<4){native_ownership();return 0;}
    sync_scene();
    if(R(Player_StatusFlag)&2) {
        native_ownership();return 0;
    }
    guest(F_Player_CheckIfOnLadder,0,0,0);
    int on_ladder=!!(R(Player_Flags)&8);
    int climbing=on_ladder&&((raw_pad&0x0c)||(R(Player_Flags)&0x10))&&!(raw_pad&0x80);
    if(climbing&&!(S.effects&(1u<<LINK_FAIRY_SPELL))) {
        native_ownership();return 0;
    }
    if(!S.foreign)reseed();
    S.ladder_jump=(uint8_t)(on_ladder&&(raw_changed&0x80));
    S.foreign=1;nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);return 0;
}
static int tick_hook(uint16_t addr) {
    (void)addr;if(!S.foreign) {
        S.thunder=0;advance_projectiles();W(Player_Flags,R(Player_Flags)&~0x80);
        return 1;
    }
    ++S.ticks;
    S.thunder=0; /* A single cast affects this tick's existing actors only. */
    memset(&S.collision,0,sizeof S.collision);
    int beam=0;for(int i=0;i<LINK_PROJECTILES;i++)beam|=S.projectile[i].life&&S.projectile[i].kind==1;
    ForeignState *s=nes_foreign_state();
    int fairy=(S.effects&(1u<<LINK_FAIRY_SPELL))!=0;
    s->grounded=S.ladder_jump||(!fairy&&link_private()->vertical>=0&&
        blocked(R(Player_PosX_Block),R(Player_PosY)+1,0,s->state==LINK_CROUCH));
    S.ladder_jump=0;
    ForeignInput input={0};
    input.stick_x=(float)((raw_pad&1)!=0)-((raw_pad&2)!=0);
    input.stick_y=(float)((raw_pad&8)!=0)-((raw_pad&4)!=0);
    input.jump_pressed=!!(raw_changed&0x80);input.jump_held=!!(raw_pad&0x80);
    input.attack_pressed=!!(raw_changed&0x40);input.raw_buttons=raw_pad;
    if(((raw_pad&8)&&(raw_changed&0x40))||S.shortcut_cast) {
        cast();S.shortcut_cast=0;input.attack_pressed=0;
        W(Joy1_ButtonMask,raw_pad&~0x48);W(Joy1_ChangedButtonMask,raw_changed&~0x48);
    }
    link_environment(S.effects,R(Player_HP_U)>=80,beam);
    nes_foreign_tick(S.ticks,&input,&move);
    uint8_t flags=R(Player_Flags)&0x08;
    if(s->facing>0)flags|=0x40;
    if(move.requested_dx)flags|=0x20;
    if(!s->grounded)flags|=move.requested_dy<0?0x01:0x04;
    W(Player_Flags,flags);
    W(Player_AttackPhaseAnimFrame,0);W(Player_AttackPhaseTimer,0);
    if(move.audio.count)fax_link_audio_cue(1);
    for(unsigned i=0;i<move.actions.count;i++) {
        ForeignActionEvent *e=&move.actions.events[i];
        spawn(e->kind,(int)s->x+(s->facing>0?24:-8),(int)s->y+32-(int)e->offset_y,s->facing>0?1:-1);
    }
    advance_projectiles();
    return 1;
}
static int scroll(int dir) {
    unsigned next=Q(F_Area_ScreenToTheLeft+dir);if(next==255)return 0;
    W(Area_CurrentScreen,next);
    if(dir==1)W(Screen_Maybe_ScrollXCounter,R(Screen_Maybe_ScrollXCounter)+1);
    if(dir==2)W(Player_Something_ScrollPosY,R(Player_Something_ScrollPosY)-1);
    if(dir==3)W(Player_Something_ScrollPosY,R(Player_Something_ScrollPosY)+1);
    W(Screen_ScrollPlayerTransitionCounter,0);
    int fairy=S.effects&(1u<<LINK_FAIRY_SPELL);
    clear_scene();if(fairy){S.effects=1u<<LINK_FAIRY_SPELL;S.fairy_pending_end=1;}
    S.foreign=0;return tail(F_Area_ScrollTo,dir);
}
static int vertical_hook(uint16_t addr) {
    (void)addr;if(!S.foreign)return 0;
    ForeignState *s=nes_foreign_state();ForeignCollisionResult hit={0};
    int x=R(Player_PosX_Block),y=R(Player_PosY);
    double old=s->y,target=old+move.requested_dy;
    int dy=(int)floor(target)-y,dir=dy>=0?1:-1,stopped=0;
    int fairy=!!(S.effects&(1u<<LINK_FAIRY_SPELL));int crouch=s->state==LINK_CROUCH||s->state==LINK_CROUCH_SLASH;
    int start=y;
    for(int i=0;i<abs(dy);i++) {
        if(blocked(x,y+dir,fairy,crouch)){if(dir>0)hit.hit_floor=1;else hit.hit_ceiling=1;stopped=1;break;}
        y+=dir;
        if(y<0||y>192) {
            int direction=y<0?2:3;
            if(Q(F_Area_ScreenToTheLeft+direction)!=255) {
                W(Player_PosY,y<0?192:0);return scroll(direction);
            }
            y=y<0?0:192;hit.hit_wall=1;stopped=1;break;
        }
    }
    (void)start;hit.actual_dy=(stopped?y:target)-old;hit.grounded=!fairy&&blocked(x,y+1,0,crouch);
    S.collision=hit;W(Player_PosY,y);
    return 1;
}
static int horizontal_hook(uint16_t addr) {
    (void)addr;if(!S.foreign)return 0;
    /* Native hit reaction has priority. Its velocity/position becomes the
     * next foreign seed, rather than being erased by a second integrator. */
    if(R(Player_StatusFlag)&2){S.foreign=0;nes_foreign_resolve(&S.collision);return 0;}
    ForeignState *s=nes_foreign_state();ForeignCollisionResult hit=S.collision;
    double old=s->x,target=old+move.requested_dx;int x=R(Player_PosX_Block),y=R(Player_PosY);
    int dest=(int)floor(target),dir=dest>=x?1:-1,stopped=0;
    int fairy=!!(S.effects&(1u<<LINK_FAIRY_SPELL));int crouch=s->state==LINK_CROUCH||s->state==LINK_CROUCH_SLASH;
    while(x!=dest) {
        if(blocked(x+dir,y,fairy,crouch)){hit.hit_wall=1;stopped=1;break;}
        x+=dir;
        if(x<0||x>240) {
            int direction=x<0?0:1;
            if(Q(F_Area_ScreenToTheLeft+direction)!=255) {
                W(Player_PosX_Block,x<0?0:241);W(Player_PosX_Frac,0);return scroll(direction);
            }
            x=x<0?0:240;hit.hit_wall=1;stopped=1;break;
        }
    }
    hit.actual_dx=(stopped?x:target)-old;
    hit.grounded=!fairy&&blocked(x,y+1,0,crouch);
    nes_foreign_resolve(&hit);W(Player_PosX_Block,x);W(Player_PosX_Frac,(unsigned)((s->x-floor(s->x))*256));
    W(Player_MovementTick,R(Player_MovementTick)+(move.requested_dx!=0));return 1;
}
static void bounds(int slot,int *x,int *y,int *w,int *h) {
    guest(F_Sprite_GetBounds,0,slot,0);
    *x=R(SpriteBox_Left);*y=R(SpriteBox_Top);*w=R(SpriteBox_Width);*h=R(SpriteBox_Height);
}
static int sword_hook(uint16_t addr) {
    (void)addr;
    int slot=R(CurrentSpriteIndex);if(slot>7||!enemy(slot))return 1;
    int x,y,w,h;bounds(slot,&x,&y,&w,&h);int hit=0,magic=-1,contact=0;
    ForeignState *s=nes_foreign_state();
    float hit_facing=s->facing;
    if(S.foreign&&move.attack.active) {
        ForeignAttackHitbox *a=&move.attack;
        int cx=(int)s->x+(int)(s->facing*a->offset_x),cy=(int)s->y+32-(int)a->offset_y;
        contact=hit=overlap(cx-(int)a->width/2,cy-(int)a->height/2,(int)a->width,(int)a->height,x,y,w,h);
    }
    for(int i=0;i<LINK_PROJECTILES&&!hit;i++) {
        LinkProjectile *p=&S.projectile[i];if(!p->life||(p->hit&(1u<<slot)))continue;
        if(overlap(p->x/256,p->y/256,12,8,x,y,w,h)) {
            hit=1;magic=p->kind==1?-1:0;hit_facing=p->vx>0?1:-1;p->hit|=(uint8_t)(1u<<slot);p->life=0;
        }
    }
    if(S.thunder&(1u<<slot)){S.thunder&=(uint8_t)~(1u<<slot);hit=1;magic=4;}
    if(!hit)return 1;
    unsigned old_id=Q(F_CurrentSprites_Entities+slot),old_hp=Q(F_CurrentSprites_HP+slot);
    S.transformed&=(uint8_t)~(1u<<slot);
    if(magic>=0) {
        P(F_CurrentSprites_HitByMagicBehavior+slot,Q(F_CAST_MAGIC_HIT_BEHAVIORS+magic));
        P(F_CurrentSprites_HitByMagicIFrames+slot,Q(F_CAST_MAGIC_HIT_IFRAMES+magic));
        P(F_CurrentSprites_Flags+slot,(Q(F_CurrentSprites_Flags+slot)&~1)|(hit_facing>0));
        guest(F_Player_HitEnemyWithMagic,0,slot,magic);
    } else {
        uint8_t weapon=R(Player_CurWeapon),flags=R(Player_Flags);
        if(weapon>3)W(Player_CurWeapon,0);
        /* $883a is the original accepted-weapon-hit branch: direction,
         * equipment, pendant/glove, HP, XP and defeat scripts remain native. */
        W(Player_Flags,(flags&~0x40)|(hit_facing>0?0x40:0));
        guest(0x883a,0,slot,0);W(Player_CurWeapon,weapon);W(Player_Flags,flags);
    }
    if(contact&&s->state==LINK_DOWNSTAB)link_bounce();
    if(contact&&s->state==LINK_UPSTAB)link_upstab_contact();
    if(getenv("NESRECOMP_LINK_COMBAT_TRACE"))fprintf(stderr,
        "[Link hit] tick=%llu slot=%d entity=%02x hp=%u->%u type=%02x magic=%d contact=%d\n",
        (unsigned long long)S.ticks,slot,old_id,old_hp,Q(F_CurrentSprites_HP+slot),Q(F_CurrentSprites_Entities+slot),magic,contact);
    return 1;
}
static int shield_hook(uint16_t addr) {
    (void)addr;if(!S.foreign)return 1;
    int slot=R(CurrentSpriteIndex);if(slot>7||category(slot)!=6)return 1;
    ForeignState *s=nes_foreign_state();
    if(s->state==LINK_SLASH||s->state==LINK_CROUCH_SLASH||s->state==LINK_UPSTAB||s->state==LINK_DOWNSTAB||s->state==LINK_FAIRY)return 1;
    int x=R(SpriteBox_Left),y=R(SpriteBox_Top),w=R(SpriteBox_Width),h=R(SpriteBox_Height);
    unsigned tier=R(SelectedShield)<3?R(SelectedShield):0;
    int shield_x=(int)s->x+(s->facing>0?12:-3)-(s->facing<0?(int)tier:0);
    int shield_y=(int)s->y+(s->state==LINK_CROUCH?16:4)-(int)tier*2;
    if(!overlap(shield_x,shield_y,7+(int)tier,16+(int)tier*4,x,y,w,h))return 1;
    if(S.effects&(1u<<LINK_REFLECT))spawn(LINK_FIREBALL,x,y,s->facing>0?1:-1);
    /* Source Link blocks a guarded projectile completely. Enter the native
     * removal/sound branch after its Faxanadu-specific chip-damage JSR.
     * Native shield purchases widen coverage rather than reducing chip HP. */
    guest(F_Player_HandleShieldHitByMagic+3,0,slot,0);return 1;
}
static int damage_hook(uint16_t addr) {
    (void)addr;
    if(S.effects&(1u<<LINK_SHIELD)) {
        unsigned delta=R(Arg_PlayerHealthDelta_L)|(R(Arg_PlayerHealthDelta_U)<<8);
        delta=(delta+1)/2;W(Arg_PlayerHealthDelta_L,delta);W(Arg_PlayerHealthDelta_U,delta>>8);
    }
    return 0;
}
static int magic_hook(uint16_t addr) {(void)addr;W(CastMagic_Type,255);return 1;}
static int item_hook(uint16_t addr) {
    (void)addr;
    if((raw_pad&4)&&(raw_changed&0x10)) {
        W(Joy1_ButtonMask,(raw_pad&~0x30)|0x44);
        W(Joy1_ChangedButtonMask,0x40);return 0;
    }
    return 1; /* Down+B belongs to Link's crouching sword attack. */
}
static int inventory_hook(uint16_t addr) {
    (void)addr;
    if(raw_changed&0x10) {
        W(Joy1_ButtonMask,raw_pad&~0x10);
        W(Joy1_ChangedButtonMask,raw_changed&~0x10);
        if(!(raw_pad&4)) {
            W(Joy1_ButtonMask,(raw_pad&~0x10)|0x20);
            W(Joy1_ChangedButtonMask,(raw_changed&~0x10)|0x20);
        }
    }
    return 0;
}
static int body_hook(uint16_t addr) {
    (void)addr;S.draw=0;S.hud_visible=0;
    if(!(R(IScript_PortraitID)&0x80))return 0;
    int scrolling=R(Screen_ReadyState)==1||R(Screen_ReadyState)==5;
    int x=scrolling?R(Maybe_PlayerX_ForScroll):R(Player_PosX_Block);
    int y=scrolling?R(Maybe_PlayerY_ForScroll):R(Player_PosY);
    S.draw_x=(int16_t)((x-R(PPU_ScrollX))&255);if(S.draw_x>248)S.draw_x-=256;
    S.draw_y=(int16_t)(y+32);S.draw=1;S.hud_visible=!S.dying;S.draw_frame=S.dying?3:(uint8_t)link_frame();
    const ForeignState *fighter=nes_foreign_state();
    if(S.draw_frame==6&&fighter&&!fighter->grounded)S.draw_y-=4;
    S.draw_left=(R(Player_Flags)&0x40)==0;
    int property=prop_at(R(Player_PosX_Block)+8,R(Player_PosY));
    S.draw_behind=property==4||property==9||property==13;
    if(R(Player_InvincibilityPhase)&2)S.draw=0;
    return 1;
}
static int equipment_hook(uint16_t addr) {(void)addr;return (R(IScript_PortraitID)&0x80)!=0;}
static int death_draw_hook(uint16_t addr) {
    body_hook(addr);
    /* The native routine still owns the dissolve timer, sound, fade, mantra
     * and retry. Its CHR erasure cannot erase host-rendered Link pixels. */
    unsigned phase=R(Player_DeathAnimationPhase);
    S.death_phase=(uint8_t)(phase==255?0:phase>8?8:phase);
    return 0;
}
static int transformed_hook(uint16_t addr) {
    (void)addr;int slot=R(CurrentSpriteIndex);
    return slot<8&&enemy(slot)&&(S.transformed&(1u<<slot));
}
static int touch_hook(uint16_t addr) {
    if(transformed_hook(addr))return 1;
    if(S.effects&(1u<<LINK_FAIRY_SPELL)) {
        if(!overlap(R(Player_PosX_Block)+4,R(Player_PosY)+12,8,8,R(SpriteBox_Left),R(SpriteBox_Top),R(SpriteBox_Width),R(SpriteBox_Height)))return 1;
    }
    const ForeignState *s=nes_foreign_state();
    if(S.foreign&&s&&(s->state==LINK_CROUCH||s->state==LINK_CROUCH_SLASH)&&
       !overlap(R(Player_PosX_Block)+3,R(Player_PosY)+18,10,14,R(SpriteBox_Left),R(SpriteBox_Top),R(SpriteBox_Width),R(SpriteBox_Height)))return 1;
    return 0;
}
static int reset_hook(uint16_t addr) {(void)addr;clear_scene();S.foreign=0;S.initialized=0;S.picker=0;S.dying=S.death_phase=0;return 0;}
static int death_hook(uint16_t addr) {reset_hook(addr);S.dying=1;return 0;}
typedef struct {const char *id;uint16_t addr;NESModFunctionEntryCallback callback;} Hook;
static const Hook hooks[]={
    {"player",F_GameLoop_UpdatePlayer,player_hook},
    {"tick",F_Player_CheckHandleAttack,tick_hook},{"vertical",F_Player_CheckHandleVertMovement,vertical_hook},
    {"horizontal",F_Player_CheckHandleJump,horizontal_hook},{"sword",F_Player_HitSpriteWithWeapon,sword_hook},
    {"shield",F_Player_CheckShieldHitByMagic,shield_hook},{"damage",F_Player_ReduceHP,damage_hook},
    {"magic",F_Player_CastMagic,magic_hook},{"body",F_Player_DrawBody,body_hook},
    {"shield-draw",F_Player_DrawShield,equipment_hook},{"sword-draw",F_Player_DrawWeapon,equipment_hook},
    {"actor-move",F_Sprites_UpdateBehavior,transformed_hook},{"actor-draw",F_CurrentSprite_UpdateState,transformed_hook},
    {"actor-touch",F_CurrentSprite_CheckHitPlayer,touch_hook},{"new-game",F_Player_SetInitialState,reset_hook},
    {"death",F_Player_HandleDeath,death_hook},{"death-draw",F_Player_DrawDeathAnimation,death_draw_hook},
    {"inventory",F_GameLoop_CheckShowPlayerMenu,inventory_hook},{"item",F_GameLoop_CheckUseCurrentItem,item_hook},
};
/* Function-hook registry retains ids; each needs static storage. */
static char hook_ids[sizeof hooks/sizeof hooks[0]][96];
static void set_hooks(int on) {
    for(unsigned i=0;i<sizeof hooks/sizeof hooks[0];i++){
        nes_mod_set_function_hook_enabled(hook_ids[i],on);
    }
}
static void deactivate(void) {
    set_hooks(0);enabled=0;nes_foreign_select(NULL);cyc_render_capture_background(false);
    nes_mod_set_local_only("Play as Link",0);nes_mod_audio_stop_all();
}
static void activate(void) {
    const char *path=nes_mod_external_rom_path(LINK_PACKAGE,LINK_FEATURE,"zelda2-us");
    if(!path||!fax_link_load_assets(path)||!nes_foreign_select(LINK_CONTROLLER_ID)) {
        fprintf(stderr,"[Link] Failed to load verified Zelda II owner ROM\n");abort();
    }
    enabled=1;fax_link_power_on();set_hooks(1);
    nes_mod_set_local_only("Play as Link",1);
    fprintf(stderr,"[Link] Zelda II Link active: A jump, B sword, Select spells, Up+B cast\n");
}
int fax_link_active(void){return enabled;}
void fax_link_power_on(void){memset(&S,0,sizeof S);S.version=1;memset(&move,0,sizeof move);}
void fax_link_frame_begin(void) {if(enabled){S.previous_draw=S.draw;S.draw=0;S.hud_visible=0;}}
void fax_link_frame_end(void) {if(enabled&&S.flash)--S.flash;}
const uint32_t *fax_link_present(int *w,int *h) {
    if(!enabled)return NULL;
    memcpy(picture,S.picker?frozen:cyc_frame_argb(),sizeof picture);
    fax_link_render(picture);*w=256;*h=240;return picture;
}
static int state_get(uint8_t *buf,int cap) {
    if(!enabled)return 0;
    int size=(int)(sizeof S+sizeof move+sizeof(ForeignState)+sizeof(LinkPrivate)+sizeof frozen);
    if(size>cap)return -1;memcpy(buf,&S,sizeof S);memcpy(buf+sizeof S,&move,sizeof move);
    uint8_t *at=buf+sizeof S+sizeof move;
    memcpy(at,nes_foreign_state(),sizeof(ForeignState));at+=sizeof(ForeignState);
    memcpy(at,link_private(),sizeof(LinkPrivate));at+=sizeof(LinkPrivate);
    memcpy(at,frozen,sizeof frozen);return size;
}
static int state_validate(const uint8_t *buf,int len) {
    if(!enabled)return len==0;
    if(!buf)return len==0;
    if(len!=sizeof S+sizeof move+sizeof(ForeignState)+sizeof(LinkPrivate)+sizeof frozen)return 0;
    FaxLinkState next;memcpy(&next,buf,sizeof next);
    if(next.version!=1||next.spell>=8||next.cursor>=8||next.picker>1||next.foreign>1||next.draw_frame>=20||
       next.hud_visible>1||next.fairy_pending_end>1||next.dying>1||next.death_phase>8||(next.effects&~0x3b))return 0;
    for(int i=0;i<LINK_PROJECTILES;i++)if(next.projectile[i].life>128||next.projectile[i].kind>2||
        next.projectile[i].x< -4096||next.projectile[i].x>69632||next.projectile[i].y< -4096||next.projectile[i].y>69632||
        llabs((int64_t)next.projectile[i].vx)>1024)return 0;
    ForeignMoveResult m;memcpy(&m,buf+sizeof S,sizeof m);
    if(!isfinite(m.requested_dx)||!isfinite(m.requested_dy)||fabs(m.requested_dx)>8||fabs(m.requested_dy)>8||
       !isfinite(m.vx)||!isfinite(m.vy)||fabs(m.vx)>8||fabs(m.vy)>8||
       m.actions.count>FOREIGN_ACTION_EVENT_CAPACITY||m.audio.count>FOREIGN_AUDIO_EVENT_CAPACITY||
       !isfinite(m.attack.offset_x)||!isfinite(m.attack.offset_y)||!isfinite(m.attack.width)||!isfinite(m.attack.height)||
       fabs(m.attack.offset_x)>64||fabs(m.attack.offset_y)>64||m.attack.width<0||m.attack.width>64||m.attack.height<0||m.attack.height>64||
       !isfinite(next.collision.actual_dx)||!isfinite(next.collision.actual_dy)||
       !isfinite(next.collision.imposed_vy)||fabs(next.collision.imposed_vy)>8||
       fabs(next.collision.actual_dx)>8||fabs(next.collision.actual_dy)>8)return 0;
    ForeignState f;LinkPrivate p;const uint8_t *at=buf+sizeof S+sizeof move;
    memcpy(&f,at,sizeof f);memcpy(&p,at+sizeof f,sizeof p);
    if(!link_private_validate(&p)||f.state<LINK_STAND||f.state>LINK_FAIRY||
       !isfinite(f.x)||!isfinite(f.y)||!isfinite(f.vx)||!isfinite(f.vy)||!isfinite(f.facing)||
       f.x< -16||f.x>272||f.y< -16||f.y>272||fabs(f.vx)>8||fabs(f.vy)>8||fabs(f.facing)!=1)return 0;
    return 1;
}
static int state_set(const uint8_t *buf,int len) {
    if(!state_validate(buf,len))return 0;if(!enabled)return 1;
    if(!buf){fax_link_power_on();reseed();return 1;}
    memcpy(&S,buf,sizeof S);memcpy(&move,buf+sizeof S,sizeof move);
    ForeignState f;LinkPrivate p;const uint8_t *at=buf+sizeof S+sizeof move;
    memcpy(&f,at,sizeof f);at+=sizeof f;memcpy(&p,at,sizeof p);at+=sizeof p;
    if(!link_restore(&f,&p))return 0;memcpy(frozen,at,sizeof frozen);
    nes_foreign_set_ownership(S.foreign?FOREIGN_OWNERSHIP_FOREIGN:FOREIGN_OWNERSHIP_SCRIPTED);
    nes_mod_audio_stop_all();return 1;
}
void fax_link_event(const void *event) {
#ifdef CYC_WITH_SDL
    const SDL_Event *e=event;if(!enabled||e->type!=SDL_KEYDOWN||e->key.repeat)return;
    if(cast_key&&e->key.keysym.scancode==cast_key)S.shortcut_cast=1;
    if(picker_key&&e->key.keysym.scancode==picker_key)S.shortcut_picker=1;
#else
    (void)event;
#endif
}
int fax_link_load_setting(const char *key,const char *value) {
    int *target=!strcmp(key,"LinkCastKey")?&cast_key:!strcmp(key,"LinkPickerKey")?&picker_key:NULL;
    if(!target)return 0;char *end;long v=strtol(value,&end,10);if(!*end&&v>=0&&v<512)*target=(int)v;return 1;
}
void fax_link_save_settings(void *file) {fprintf((FILE*)file,"LinkCastKey = %d\nLinkPickerKey = %d\n",cast_key,picker_key);}
#ifdef CYC_WITH_SDL
static void status(int id,const char *line) {
    (void)line;char fields[512];const ForeignState *s=nes_foreign_state();
    snprintf(fields,sizeof fields,"\"active\":%s,\"tick\":%llu,\"foreign\":%u,\"spell\":\"%s\",\"effects\":%u,\"picker\":%u,\"x\":%.4f,\"y\":%.4f,\"vx\":%.4f,\"vy\":%.4f,\"hp\":%u,\"mp\":%u",enabled?"true":"false",(unsigned long long)S.ticks,S.foreign,link_spell_name(S.spell),S.effects,S.picker,s?s->x:0,s?s->y:0,s?s->vx:0,s?s->vy:0,R(Player_HP_U),R(Player_MP));
    cyc_tcp_ok(id,fields);
}
#endif
void fax_link_tcp_setup(void) {
#ifdef CYC_WITH_SDL
    cyc_tcp_register("link_status","Link controller, spell and world-adapter state",status);
#endif
}
NES_MOD_CONSTRUCTOR(register_fax_link) {
    nes_foreign_trace_init_dump();
    if(!link_controller_register())abort();
    for(unsigned i=0;i<sizeof hooks/sizeof hooks[0];i++){
        snprintf(hook_ids[i],sizeof hook_ids[i],"faxanadu.link.%s",hooks[i].id);
        if(!nes_mod_register_function_entry_plugin(hook_ids[i],hooks[i].addr,hooks[i].callback)){
            fprintf(stderr,"[Link] Could not register %s\n",hook_ids[i]);abort();
        }
    }
    if(!nes_mod_register_reset_callback(deactivate)||!nes_mod_register_activation_plugin(LINK_CONTROLLER_ID,activate)||
       !nes_mod_register_savestate_hook("faxanadu.zelda2.adapter",state_get,state_set)||
       !nes_mod_register_savestate_validator("faxanadu.zelda2.adapter",state_validate))abort();
}
