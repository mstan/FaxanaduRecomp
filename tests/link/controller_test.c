/* Execute ORIGINAL Zelda II 6502 routines against the port. The test bus is
 * a read-only bank0+bank7 ROM and scratch RAM, with collision stubbed out
 * only at the source's world-motion call. No ROM bytes are checked in. */
#include "mods/zelda2/link_controller.h"
#include "cpu6502.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static uint8_t memory[65536];
bool cyc_trace_enabled;uint64_t cyc_trace_hash;void *cyc_trace_file;
int hw_dma_stalls;bool hw_frame_done;
void hw_cycle_start(uint16_t a,HwCycleKind k){(void)a;(void)k;}
void hw_cycle_finish(bool done){(void)done;}
uint8_t hw_read(uint16_t a){return memory[a];}
uint8_t hw_read_rom(uint16_t a,uint8_t v){(void)a;return v;}
void hw_write(uint16_t a,uint8_t v){if(a<0x8000)memory[a]=v;}
bool hw_irq_line(void){return false;}
void cyc_trace_instruction(uint16_t pc,uint8_t a,uint8_t x,uint8_t y,uint8_t s,uint8_t p){(void)pc;(void)a;(void)x;(void)y;(void)s;(void)p;}
static unsigned checks;
#define CHECK(test) do{++checks;if(!(test)){fprintf(stderr,"FAIL line %u: %s\n",__LINE__,#test);exit(1);}}while(0)
static void call(uint16_t entry) {
    memset(&cpu,0,sizeof cpu);cpu.pc=entry;cpu.s=0xfd;memory[0x1fe]=0xff;memory[0x1ff]=0x02;
    for(unsigned i=0;i<2000&&cpu.pc!=0x0300;i++) {
        if(cpu.pc==0x9610) { /* source world-motion call, not locomotion logic */
            uint16_t ret=memory[0x100|++cpu.s];ret|=memory[0x100|++cpu.s]<<8;cpu.pc=ret+1;
        } else cpu_interp_step();
    }
    CHECK(cpu.pc==0x0300);
}
static void clear(void){memset(memory,0,0x8000);nes_foreign_select(LINK_CONTROLLER_ID);nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);}
static void walking(void) {
    for(int air=0;air<2;air++)for(int speed=-24;speed<=24;speed++)for(int dir=-1;dir<=1;dir++) {
        clear();ForeignState *s=nes_foreign_state();LinkPrivate p=*link_private();
        s->grounded=!air;p.speed=(int16_t)speed;p.motion_direction=speed<0?2:1;
        CHECK(link_restore(s,&p));
        memory[0x70]=(uint8_t)speed;memory[0x5f]=p.motion_direction;
        memory[0x17]=1;memory[0x0479]=(uint8_t)air;
        memory[0x0742]=dir<0?2:dir>0?1:0;
        call(0x93bc);
        ForeignInput in={0};in.stick_x=(float)dir;ForeignMoveResult out;
        nes_foreign_tick(1,&in,&out);
        if(link_private()->speed!=(int8_t)memory[0x70]) {
            fprintf(stderr,"walking air=%d speed=%d dir=%d native=%d port=%d\n",air,speed,dir,(int8_t)memory[0x70],link_private()->speed);exit(1);
        }
        CHECK(fabs(out.requested_dx-(int8_t)memory[0x70]/16.0)<1e-9);
    }
}
static void jumps(void) {
    for(int jump=0;jump<2;jump++)for(int running=0;running<2;running++)for(int held=0;held<2;held++) {
        clear();ForeignState *s=nes_foreign_state();LinkPrivate p=*link_private();
        p.speed=running?24:0;CHECK(link_restore(s,&p));
        memory[0x70]=(uint8_t)p.speed;memory[0x29]=128;memory[0x19]=1;
        memory[0xa7]=4;memory[0x0741]=0x80;memory[0xf7]=held?0x80:0;memory[0xd0]=(uint8_t)jump;
        link_environment(jump?(1u<<LINK_JUMP):0,1,0);
        for(int tick=0;tick<48;tick++) {
            int before=memory[0x29];call(0x94c5);
            ForeignInput in={0};in.jump_pressed=tick==0;in.jump_held=held;in.stick_x=running?1:0;
            ForeignMoveResult out;nes_foreign_tick(tick,&in,&out);
            int delta=(int8_t)(memory[0x29]-before);
            if(out.requested_dy!=delta||link_private()->vertical!=(int8_t)memory[0x057d]||link_private()->gravity_fraction!=memory[0x03e6]) {
                fprintf(stderr,"jump=%d run=%d held=%d tick=%d native dy=%d v=%d g=%u port dy=%.3f v=%d g=%u\n",jump,running,held,tick,delta,(int8_t)memory[0x057d],memory[0x03e6],out.requested_dy,link_private()->vertical,link_private()->gravity_fraction);exit(1);
            }
            CHECK(out.requested_dy==delta);
            ForeignCollisionResult h={0};h.actual_dy=delta;nes_foreign_resolve(&h);
            memory[0x0741]=0;memory[0xa7]=0;
        }
    }
}
static void behavior(void) {
    clear();ForeignInput in={0};ForeignMoveResult out;ForeignState *s=nes_foreign_state();
    s->grounded=0;in.stick_y=-1;nes_foreign_tick(0,&in,&out);CHECK(s->state==LINK_DOWNSTAB&&out.attack.active);
    link_bounce();CHECK(link_private()->vertical<0);
    clear();link_environment(0,1,0);in=(ForeignInput){0};in.attack_pressed=1;
    int beams=0;for(int t=0;t<45;t++){nes_foreign_tick(t,&in,&out);beams+=(int)out.actions.count;in.attack_pressed=0;}
    CHECK(beams==1);
    clear();link_environment(0,0,0);in.attack_pressed=1;
    beams=0;for(int t=0;t<45;t++){nes_foreign_tick(t,&in,&out);beams+=(int)out.actions.count;in.attack_pressed=0;}
    CHECK(beams==0);
    clear();link_environment(1u<<LINK_FAIRY_SPELL,1,0);in=(ForeignInput){0};in.stick_y=1;
    nes_foreign_tick(0,&in,&out);CHECK(s->state==LINK_FAIRY&&out.requested_dy<0&&!out.attack.active);
    unsigned costs[]={10,5,32,25,10,10,10,40};for(unsigned i=0;i<8;i++)CHECK(link_spell_cost(i,80)==costs[i]);
    uint8_t saved[2048];int n=nes_foreign_serialize_active(saved,sizeof saved);CHECK(n>0);
    ForeignState expected=*s;LinkPrivate expected_p=*link_private();
    nes_foreign_tick(1,&in,&out);CHECK(nes_foreign_deserialize_active(saved,n));
    CHECK(!memcmp(s,&expected,sizeof expected)&&!memcmp(link_private(),&expected_p,sizeof expected_p));
    saved[0]=255;CHECK(!nes_foreign_deserialize_active(saved,n));CHECK(!memcmp(s,&expected,sizeof expected));
}
static void sword_timing(void) {
    for(int crouch=0;crouch<2;crouch++) {
        clear();memory[0x9f]=1;memory[0x17]=!crouch;memory[0xa7]=4;
        call(0x95dc);link_environment(0,1,0);
        for(int t=0;t<50;t++) {
            if(t&&memory[0x050a])--memory[0x050a];
            call(0x93bc);call(0x9483);
            ForeignInput in={0};in.attack_pressed=t==0;in.stick_y=crouch?-1:0;
            ForeignMoveResult out;nes_foreign_tick(t,&in,&out);
            CHECK(link_private()->slash_phase==memory[0x0400]);
            if(memory[0x0400]) {
                CHECK(link_private()->slash_timer==memory[0x050a]);
                if(link_frame()!=memory[0x80]) {
                    fprintf(stderr,"slash crouch=%d tick=%d native frame=%u port=%u\n",crouch,t,memory[0x80],link_frame());exit(1);
                }
                CHECK(out.attack.active==(memory[0x80]==5||memory[0x80]==7));
            }
            int beam=memory[0x0400]==(unsigned)(crouch?1:2)&&memory[0x050a]==5;
            CHECK(out.actions.count==(unsigned)beam);
            if(beam)CHECK(out.actions.events[0].velocity_x==memory[0x9819]/16.0);
        }
    }
}
static void walking_animation(void) {
    clear();memory[0x5f]=1;memory[0xa7]=4;unsigned random=0x13579;
    for(int t=0;t<1000;t++) {
        random=random*1664525u+1013904223u;int dir=(int)((random>>16)%3)-1;
        int down=(random>>25)%5==0;
        memory[0x17]=!down;memory[0x0742]=dir>0?1:dir<0?2:0;
        if(memory[0x0501])--memory[0x0501];
        call(0x93bc);
        if((int8_t)memory[0x70])memory[0x5f]=(int8_t)memory[0x70]>0?1:2;
        ForeignInput in={0};in.stick_x=(float)dir;in.stick_y=down?-1:0;
        ForeignMoveResult out;nes_foreign_tick(t,&in,&out);
        CHECK(link_private()->speed==(int8_t)memory[0x70]);
        CHECK(link_private()->walk_timer==memory[0x0501]);
        CHECK(link_private()->walk_frame==memory[0xae]);
        CHECK(link_frame()==memory[0x80]);
    }
}
static void contact_motion(void) {
    CHECK(memory[0xe664]==0xa9&&memory[0xe665]==0xfe);
    for(unsigned fraction=0;fraction<256;fraction+=17) {
        clear();ForeignState *s=nes_foreign_state();LinkPrivate p=*link_private();
        p.vertical=5;p.gravity_fraction=(uint8_t)fraction;CHECK(link_restore(s,&p));
        memory[0x03e6]=(uint8_t)fraction;call(0xe664);link_bounce();
        CHECK(link_private()->vertical==(int8_t)memory[0x057d]);
        CHECK(link_private()->gravity_fraction==memory[0x03e6]);
    }
}
int main(int argc,char **argv) {
    CHECK(argc==2);FILE *f=fopen(argv[1],"rb");CHECK(f!=NULL);fseek(f,0,SEEK_END);long n=ftell(f),base=n==262160?16:0;
    CHECK(n==262160||n==262144);fseek(f,base,SEEK_SET);CHECK(fread(memory+0x8000,1,0x4000,f)==0x4000);
    fseek(f,base+7*0x4000,SEEK_SET);CHECK(fread(memory+0xc000,1,0x4000,f)==0x4000);fclose(f);
    CHECK(memory[0x93bc]==0xad&&memory[0x94c5]==0xad);
    CHECK(link_controller_register());walking();walking_animation();jumps();sword_timing();contact_motion();behavior();printf("PASS %u source-ROM and controller checks\n",checks);return 0;
}
