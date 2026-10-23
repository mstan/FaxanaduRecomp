/* Zelda II USA side view: prg0 $93b1-$960f, prg7 $d19b-$d1cd.
 * One pixel is one source pixel. No SMB scale, jump boost, or host RAM here.
 * Horizontal motion is 4.4 fixed point. Vertical motion adds the SIGNED
 * INTEGER velocity before updating its gravity accumulator, as the ROM does.
 */
#include "link_controller.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

static LinkPrivate p;
static const char *const names[]={"Shield","Jump","Life","Fairy","Fire","Reflect","Spell","Thunder"};
const char *link_spell_name(unsigned i) { return i<8?names[i]:"?"; }
unsigned link_spell_cost(unsigned i,unsigned max_mp) {
    /* prg0 $8d7b: level-eight column, maximum source magic = 8*32. */
    static const uint8_t cost[]={0x20,0x10,0x64,0x50,0x20,0x20,0x20,0x80};
    if(i>=8 || !max_mp)return 0;
    return (cost[i]*max_mp+255u)/256u;
}
const LinkPrivate *link_private(void) {return &p;}
void link_environment(uint8_t effects,int full,int beam) {
    p.effects=effects;p.full_health=(uint8_t)!!full;p.beam_live=(uint8_t)!!beam;
}
/* prg7 $e664/$e71e: a downstab changes only the integer velocity to -2. */
void link_bounce(void) {p.vertical=-2;}
void link_upstab_contact(void) {p.vertical=0;}
static void reset(ForeignState *s) {
    memset(&p,0,sizeof p);memset(s,0,sizeof *s);
    s->facing=1;s->grounded=1;s->state=LINK_STAND;p.motion_direction=1;
}
static void projectile(ForeignMoveResult *out,unsigned kind,int crouch) {
    ForeignActionEvent *e=&out->actions.events[out->actions.count++];
    e->kind=kind;e->command=FOREIGN_ACTION_SPAWN;
    /* Source $9847/$97f1: beam sprite Y is Link Y + 0/10 (stand/duck),
     * fire Y is +4/13. The event uses the controller's bottom-origin ABI. */
    int y=kind==LINK_BEAM?(crouch?10:0):(crouch?13:4);
    e->offset_x=24;e->offset_y=32-y;e->velocity_x=2;
    e->width=4;e->height=6;e->damage=1;e->lifetime_ticks=kind==LINK_BEAM?32:128;
    e->flags=FOREIGN_ACTION_HOSTILE|FOREIGN_ACTION_DESTROY_ON_SOLID;
}
static void tick(ForeignState *s,const ForeignInput *in,ForeignMoveResult *out) {
    int dir=(in->stick_x>0)-(in->stick_x<0),down=in->stick_y<-.5f;
    int old=s->state, swing_start=0;
    memset(out,0,sizeof *out);s->jump_phase=FOREIGN_JUMP_NONE;
    if(p.walk_timer)--p.walk_timer;
    if(dir)s->facing=(float)dir;
    if(p.effects&(1u<<LINK_FAIRY_SPELL)) {
        /* prg0 $92aa/$92b4: Fairy uses +/-$18 in 4.4 units (1.5px). */
        p.speed=(int16_t)(dir*24);p.vertical=0;
        p.gravity_fraction=0;p.slash_phase=0;s->state=LINK_FAIRY;
        out->requested_dx=p.speed/16.0;out->requested_dy=-((in->stick_y>0)-(in->stick_y<0))*1.5;
    } else {
        if(in->attack_pressed && (!p.slash_phase || p.slash_phase==4)) {
            p.slash_phase=1;p.slash_timer=6;p.crouched_slash=(uint8_t)(down&&s->grounded);
            if(s->grounded)p.speed=0;
            if(p.crouched_slash)swing_start=1;
        } else if(p.slash_phase && p.slash_timer && !--p.slash_timer) {
            if((p.crouched_slash&&p.slash_phase==2)||p.slash_phase==4) {
                p.slash_phase=0;if(s->grounded)p.speed=0;
            } else {
                ++p.slash_phase;p.slash_timer=p.slash_phase==4?32:6;
                if(p.slash_phase==2&&!p.crouched_slash)swing_start=1;
            }
        }
        /* prg0 $93f1/$9401: drag 1, same-direction acceleration 1,
         * reversal acceleration 2, terminal speed +/-$18 = 1.5px/tick. */
        if(!(s->grounded&&(down||p.slash_phase))) {
            if(dir) {
                int accel=p.motion_direction!=(dir>0?1:2)?2:1;
                p.speed=(int16_t)(p.speed+dir*accel);
                if(p.speed>24)p.speed=24;
                if(p.speed< -24)p.speed=-24;
            } else if(s->grounded) p.speed+=(p.speed<0)-(p.speed>0);
        } else if(down) p.speed+=(p.speed<0)-(p.speed>0);
        if(s->grounded) {
            p.vertical=0;p.gravity_fraction=0;p.jump_started=0;
            if(in->jump_pressed) {
                int running=p.speed>=19||p.speed< -19;
                int jump=(p.effects&(1u<<LINK_JUMP))!=0;
                p.vertical=(int8_t)(jump?-5:-4);
                p.gravity_fraction=(uint8_t)(jump?(running?0:0x80):(running?0x80:0xf0));
                p.slash_phase=0;s->grounded=0;p.jump_started=1;
                s->jump_phase=FOREIGN_JUMP_LAUNCH;out->force_airborne=1;
            }
        }
        out->requested_dx=p.speed/16.0;
        out->requested_dy=s->grounded?0:p.vertical;
        if(!s->grounded) {
            unsigned gravity=in->jump_held&&p.vertical<0?0x30:0x48;
            unsigned sum=p.gravity_fraction+gravity;
            p.gravity_fraction=(uint8_t)sum;p.vertical+=(int8_t)(sum>>8);
            if(p.vertical>=5){p.vertical=5;p.gravity_fraction=0;}
        }
        if(!s->grounded&&down)s->state=LINK_DOWNSTAB;
        else if(!s->grounded&&in->stick_y>.5f&&p.vertical<0)s->state=LINK_UPSTAB;
        else if(p.slash_phase)s->state=p.crouched_slash?LINK_CROUCH_SLASH:LINK_SLASH;
        else if(!s->grounded)s->state=LINK_AIR;
        else if(down)s->state=LINK_CROUCH;
        else s->state=p.speed?LINK_WALK:LINK_STAND;
        int blade=p.crouched_slash?(p.slash_phase==1||(p.slash_phase==2&&p.slash_timer==6)):
            ((p.slash_phase==2&&p.slash_timer<6)||(p.slash_phase==3&&p.slash_timer==6));
        if(blade||s->state==LINK_UPSTAB||s->state==LINK_DOWNSTAB) {
            ForeignAttackHitbox *a=&out->attack;
            a->active=1;a->damage=1;
            if(s->state==LINK_UPSTAB){a->offset_x=8;a->offset_y=39;a->width=10;a->height=16;}
            else if(s->state==LINK_DOWNSTAB){a->offset_x=8;a->offset_y=-2;a->width=10;a->height=16;}
            else {a->offset_x=23;a->offset_y=p.crouched_slash?10:23;a->width=22;a->height=10;}
        }
        if(p.slash_phase==(p.crouched_slash?1:2)&&p.slash_timer==5) {
            if(p.effects&(1u<<LINK_FIRE))projectile(out,LINK_FIREBALL,p.crouched_slash);
            else if(p.full_health&&!p.beam_live)projectile(out,LINK_BEAM,p.crouched_slash);
        }
        if(swing_start) {
            out->audio.count=1;out->audio.events[0].cue=1;out->audio.events[0].gain_percent=100;
        }
    }
    if(p.speed) {
        static const uint8_t delay[]={8,7,5,4,3};
        p.motion_direction=p.speed>0?1:2;
        if(!p.walk_timer){p.walk_timer=delay[abs(p.speed)>>3];p.walk_frame=(p.walk_frame+1)%3;}
    }
    s->vx=p.speed/16.0;s->vy=s->state==LINK_FAIRY?out->requested_dy:p.vertical;
    s->state_frame=old==s->state?s->state_frame+1:0;
    out->vx=s->vx;out->vy=s->vy;out->state=s->state;
}
static void resolve(ForeignState *s,const ForeignCollisionResult *h) {
    s->x+=h->actual_dx;s->y+=h->actual_dy;s->grounded=h->grounded;
    if(h->hit_wall)p.speed=0;
    if(h->hit_floor){p.vertical=0;p.gravity_fraction=0;p.jump_started=0;}
    if(h->hit_ceiling&&p.vertical<0){p.vertical=-1;p.gravity_fraction=0;}
    if(h->attack_connected&&s->state==LINK_DOWNSTAB)link_bounce();
    if(h->has_imposed_vy){p.vertical=(int8_t)h->imposed_vy;p.gravity_fraction=0;}
    s->vx=p.speed/16.0;if(s->state!=LINK_FAIRY)s->vy=p.vertical;
}
unsigned link_frame(void) {
    const ForeignState *s=nes_foreign_state();if(!s)return 3;
    switch(s->state){
    case LINK_WALK:return p.walk_frame;
    case LINK_CROUCH:return 6;
    case LINK_SLASH:
        if(p.slash_phase==2)return p.slash_timer==6?4:5;
        if(p.slash_phase==3)return p.slash_timer==6?5:3;
        if(p.slash_phase==4&&p.slash_timer==32)return 3;
        return 4;
    case LINK_CROUCH_SLASH:return p.slash_phase==1||p.slash_timer==6?7:6;
    case LINK_UPSTAB:return 8;
    case LINK_DOWNSTAB:return 9;
    case LINK_AIR:return p.jump_started?(p.vertical<0?6:2):(p.speed?p.walk_frame:3);
    case LINK_FAIRY:return 14;
    default:return 3;
    }
}
static const char *state_name(ForeignMoveState st) {
    static const char *const n[]={"stand","walk","crouch","air","slash","crouch-slash","upstab","downstab","fairy"};
    return st>=LINK_STAND&&st<=LINK_FAIRY?n[st-LINK_STAND]:"?";
}
static int get_private(const ForeignState *s,uint8_t *b,int cap) {
    (void)s;if(cap<(int)sizeof p)return -1;memcpy(b,&p,sizeof p);return sizeof p;
}
static int set_private(ForeignState *s,const uint8_t *b,int len) {
    LinkPrivate next;(void)s;if(len!=sizeof next)return 0;memcpy(&next,b,sizeof next);
    if(!link_private_validate(&next))return 0;
    p=next;return 1;
}
int link_private_validate(const LinkPrivate *n) {
    return n->speed>=-24&&n->speed<=24&&n->vertical>=-8&&n->vertical<=5&&
        n->slash_phase<=4&&n->slash_timer<=32&&n->crouched_slash<=1&&n->full_health<=1&&n->beam_live<=1&&
        n->motion_direction>=1&&n->motion_direction<=2&&n->walk_timer<=8&&n->walk_frame<3;
}
int link_restore(const ForeignState *s,const LinkPrivate *n) {
    ForeignState *current=nes_foreign_state();
    if(!current||!link_private_validate(n))return 0;
    *current=*s;p=*n;return 1;
}
int link_controller_register(void) {
    static const ForeignController c={LINK_CONTROLLER_ID,"Zelda II Link",reset,tick,resolve,state_name};
    return nes_foreign_register(&c)&&nes_foreign_register_private_state(c.id,get_private,set_private);
}
