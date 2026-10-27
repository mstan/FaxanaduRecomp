/* Continuous Faxanadu world. USA 57dd23d1, chipx86 byte-exact disassembly.
 * The ROM owns terrain decoding, collision, actors, combat and progression.
 * Adjacent rooms execute original actor routines on isolated machines. Only
 * room-local state travels at a seam; inventory, player, stack and audio do not.
 * Door/region/script transitions retain their original ownership. */
#include "fax_world.h"
#include "cyc_mod.h"
#include "cyc_core.h"
#include "cyc_render.h"
#include "cyc_video.h"
#include "cyc_tcp.h"
#include "cyc_state.h"
#include "mod_runtime.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#ifdef CYC_WITH_SDL
#include <SDL.h>
#else
#include <time.h>
static uint64_t SDL_GetPerformanceCounter(void){return (uint64_t)clock();}
static uint64_t SDL_GetPerformanceFrequency(void){return CLOCKS_PER_SEC;}
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern uint32_t hw_palette_argb[512];

enum { MAX_ROOMS=83, RW=256, RH=208, HUD=32 };
typedef struct {
    uint8_t ram[2048],chr[8192],palette[32];
    uint8_t valid,live,owned,edges[4];
    int16_t x,y;
    uint64_t ticks;
} Room;
static Room rooms[MAX_ROOMS];
static const unsigned counts[8]={9,64,83,14,10,40,32,20};
static uint8_t payload[262144],local[2048];
static bool rom_ok,enabled,atlas,mask_ready,speculative;
static int area=-1,active=-1,zoom=3,fixed_w,fixed_h;
static int pre_x,pre_y,pending=-1,direction;
static int pending_y;
static unsigned ticks,last_tick,handoffs,failures,portals;
static bool player_tick;
static bool collision_active;
static bool death_mode,script_mode;
static int camera_x,camera_y,picture_w,picture_h,draw_w=1280,draw_h=720;
static uint32_t *canvas;
static size_t capacity;
static uint32_t frozen_hud[RW*HUD];
static bool hud_valid;
static Room *transfer;
static void hooks(bool on);
static uint8_t q(unsigned a);
static uint8_t collision_read(uint16_t pc,uint16_t addr,uint8_t value){
    (void)pc;
    if(!enabled||cyc_mod_isolated()||active<0||addr<0x600||addr>=0x6d0)return value;
    /* The original horizontal collision has a neighbor column, but floor,
     * ladder and jump sampling wrap X inside ScreenBuffer. While the body
     * straddles a seam, those wrapped columns belong to the right neighbor. */
    unsigned x=q(0x9e),col=addr&15;
    if((x>240&&col==0)||(pre_x>240&&x<16)){
        unsigned next=rooms[active].edges[1];
        if(next<MAX_ROOMS&&rooms[next].valid)return rooms[next].ram[addr];
    }
    unsigned row=(addr-0x600)/16;
    if(q(0xa1)>=176&&row>=13){unsigned next=rooms[active].edges[3];if(next<MAX_ROOMS&&rooms[next].valid)return rooms[next].ram[0x600+(row-13)*16+col];}
    return value;
}
static uint32_t rasters[MAX_ROOMS][RW*RH];
static uint8_t raster_blocks[MAX_ROOMS][256];
static uint8_t raster_palette[MAX_ROOMS][32],raster_chr[MAX_ROOMS][4096];
static bool raster_valid[MAX_ROOMS];
static double sim_ms,render_ms,max_seam_ms;
static FILE *trace;
static uint8_t q(unsigned a){return cyc_mod_peek((uint16_t)a);}
static void p(unsigned a,unsigned v){cyc_mod_poke((uint16_t)a,(uint8_t)v);}
static unsigned word(unsigned a){return q(a)|(q(a+1)<<8);}
static unsigned data(unsigned bank,unsigned addr){return payload[bank*16384+(addr&16383)];}
static int clamp(int v,int lo,int hi){return v<lo?lo:v>hi?hi:v;}
static bool call(unsigned pc,unsigned a,unsigned x){
    CycModRegs r={0};r.a=(uint8_t)a;r.x=(uint8_t)x;r.s=0xfd;r.p=0x24;
    return cyc_mod_call((uint16_t)pc,&r);
}
static bool bank(unsigned x){return call(0xcc1a,0,x);}
static void range(unsigned a,unsigned b){for(;a<=b;a++)local[a]=1;}
static void make_mask(void){
    if(mask_ready)return;
    range(0xba,0xc9);range(0x2bc,0x373);range(0x3e6,0x425);
    range(0x43c,0x4bb);range(0x600,0x6ff);
    range(0x66,0x69);range(0xcc,0xcd);local[0x383]=local[0xda]=local[0x42e]=1;
    range(0x379,0x37e); /* multipart actor drawing handlers */
    mask_ready=true;
}
static bool supported(void){
    if(rom_ok)return true;
    if(cyc_mod_copy_cart_payload(payload,sizeof payload)!=sizeof payload)return false;
    uint32_t crc=~0u;
    for(size_t i=0;i<sizeof payload;i++){crc^=payload[i];for(int b=0;b<8;b++)crc=(crc>>1)^((0u-(crc&1))&0xedb88320u);}
    rom_ok=(~crc==0x57dd23d1u);return rom_ok;
}
static bool scene_ready(void){return q(0xe)==0&&q(0x54)==255&&(q(0x3c7)&128)&&!q(0x438)&&q(0x13);}
static bool playing(void){return !death_mode&&!script_mode&&scene_ready()&&!q(0x120)&&q(0x100)==14;}
static int death_hook(uint16_t pc){(void)pc;if(enabled&&!cyc_mod_isolated())death_mode=true;return 0;}
/* Drain only scratch-machine PPU packets. Graphics loads are original native
 * routines; their normal NMI queue is collected without waiting for hardware.
 * These hooks are enabled only inside our isolated scope. */
static void drain(void){
    if(!transfer)return;
    unsigned rp=q(0x1f),wp=q(0x20),guard=0;
    while(rp!=wp&&guard++<256){
        unsigned n=q(0x500+rp);rp=(rp+1)&255;
        if(!n||n>0x40){failures++;break;}
        unsigned addr=q(0x500+rp)<<8;rp=(rp+1)&255;
        addr|=q(0x500+rp);rp=(rp+1)&255;
        for(unsigned i=0;i<n;i++){
            unsigned v=q(0x500+rp);rp=(rp+1)&255;
            if(addr<8192)transfer->chr[addr]=(uint8_t)v;
            else if(addr>=0x3f00&&addr<0x3f20)transfer->palette[addr&31]=(uint8_t)v;
            addr++;
        }
    }
    p(0x1f,wp);
}
static int queue_hook(uint16_t pc){(void)pc;if(!speculative)return 0;drain();return 0;}
static int wait_hook(uint16_t pc){(void)pc;if(!speculative)return 0;drain();return 1;}
static void capture(unsigned id,bool graphics){
    Room *r=&rooms[id];memcpy(r->ram,cyc_cpu_ram(),2048);
    if(graphics){for(unsigned i=0;i<8192;i++)r->chr[i]=cyc_render_chr((uint16_t)i);memcpy(r->palette,cyc_ppu_palette(),32);}
    r->live=r->valid=1;
}
static void load(unsigned id){
    Room *r=&rooms[id];for(unsigned i=0;i<2048;i++)if(local[i])p(i,r->ram[i]);
    p(0x63,id);p(0x64,id);
}
static bool decode(unsigned id){
    if(!cyc_mod_isolate_begin())return false;
    bool ok=bank(q(0x8c))&&call(0xd1f6,id,0);
    if(ok){memcpy(rooms[id].ram,cyc_cpu_ram(),2048);rooms[id].valid=1;}
    cyc_mod_isolate_end();if(!ok)failures++;return ok;
}
static void topology(unsigned current){
    unsigned n=counts[area],queue[MAX_ROOMS],head=0,tail=0;
    int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};unsigned reverse[4]={1,0,3,2};
    for(unsigned i=0;i<n;i++){rooms[i].owned=0;memset(rooms[i].edges,255,4);}
    rooms[current].owned=1;rooms[current].x=rooms[current].y=0;queue[tail++]=current;
    unsigned scroll=word(0x8a);
    while(head<tail){unsigned id=queue[head++];Room *r=&rooms[id];
        for(unsigned d=0;d<4;d++){
            unsigned next=data(3,scroll+id*4+d);
            if(next>=n||data(3,scroll+next*4+reverse[d])!=id)continue;
            int x=r->x+dx[d],y=r->y+dy[d];bool occupied=false;
            for(unsigned j=0;j<n;j++)if(rooms[j].owned&&rooms[j].x==x&&rooms[j].y==y&&j!=next)occupied=true;
            if(occupied)continue;
            Room *s=&rooms[next];
            if(!s->owned){s->owned=1;s->x=(int16_t)x;s->y=(int16_t)y;queue[tail++]=next;}
            if(s->x==x&&s->y==y)r->edges[d]=(uint8_t)next;
        }
    }
}
static void refresh(bool completed){
    int a=q(0x24),id=q(0x63);if(a<0||a>7||id>=(int)counts[a])return;
    if(area!=a){memset(rooms,0,sizeof rooms);memset(raster_valid,0,sizeof raster_valid);area=a;active=-1;}
    if(!rooms[id].owned)topology(id);
    bool changed=active!=id;
    if(changed){if(active>=0)portals++;active=id;}
    /* Player entry runs after the ROM clears OAM. Keep the last completed
     * scene until this tick actually finishes drawing, including when an
     * actor interrupts the tick to start a conversation. */
    if(completed||changed||!rooms[id].live)capture(id,true);
    for(unsigned i=0;i<counts[area];i++)if(rooms[i].owned&&!rooms[i].valid)decode(i);
}
static int script_hook(uint16_t pc){
    (void)pc;
    if(!enabled||cyc_mod_isolated()||death_mode||script_mode||active<0||
       area!=q(0x24)||active!=q(0x63))return 0;
    /* Dialogue can begin in the middle of the actor loop. The original
     * paused drawing routine completes the whole pose without advancing
     * AI or interactions. Run it before portrait loading clears OAM and
     * replaces sprite graphics/palettes, then retain that scene throughout
     * opening, text, and closing. Never change the live guest here. */
    if(cyc_mod_isolate_begin()){
        if(bank(14)&&call(0xcb47,0,0)&&call(0xdc46,0,0))capture((unsigned)active,true);
        else failures++;
        cyc_mod_isolate_end();
    }else failures++;
    script_mode=true;collision_active=false;cyc_mod_set_ram_read_hook(NULL);
    return 0;
}
static int freeze_hook(uint16_t pc){
    unsigned button=pc==0xe02b?0x10:0x20;
    if(enabled&&!cyc_mod_isolated()&&playing()&&(q(0x19)&button)&&
       active>=0&&area==q(0x24)&&active==q(0x63))
        /* The completed actor draw exists here. At the player-entry hook
         * the original game has already cleared its OAM staging buffer. */
        capture((unsigned)active,true);
    return 0;
}
static void shadow(unsigned id){
    Room *r=&rooms[id],*a=&rooms[active];
    p(0x9e,clamp(a->x*RW+q(0x9e)-r->x*RW,0,240));
    p(0xa1,clamp(a->y*RH+q(0xa1)-r->y*RH,0,176));
    p(0xad,200);p(0xae,0);p(0x2b3,255);p(0x16,0);p(0x19,0);
}
static bool initialize(unsigned id){
    Room *r=&rooms[id];
    if(!cyc_mod_isolate_begin())return false;
    for(unsigned i=0;i<8192;i++)r->chr[i]=cyc_render_chr((uint16_t)i);
    memcpy(r->palette,cyc_ppu_palette(),32);
    p(0x63,id);p(0x64,id);p(0x1f,0);p(0x20,0);
    bool ok=call(0xd127,0,0); /* Area_LoadScrollData, table + four collision borders */
    if(ok)ok=call(0xd276,0,0); /* Area_LoadBlockProperties */
    if(ok)ok=bank(14)&&call(0xc130,0,0)&&call(0xc1b4,0,0);
    transfer=r;speculative=true;cyc_mod_allow_isolated_hooks(true);
    if(ok)ok=call(0xc28d,0,0);
    drain();speculative=false;transfer=NULL;
    if(ok){capture(id,false);r->ticks=0;}
    cyc_mod_isolate_end();if(!ok)failures++;return ok;
}
static void tick_room(unsigned id){
    Room *r=&rooms[id];if(!r->live&&!initialize(id))return;
    if(!cyc_mod_isolate_begin()){failures++;return;}
    load(id);shadow(id);p(0x54,255);p(0xc,0);p(0xd,0);p(0x57,0);p(0x58,0);p(0x59,0);p(0x9f,0);p(0xa2,0);
    for(unsigned i=0x700;i<0x800;i+=4)p(i,0xf0);
    transfer=r;speculative=true;cyc_mod_allow_isolated_hooks(true);p(0x1f,0);p(0x20,0);
    bool ok=bank(14)&&call(0xcb17,0,0)&&call(0x8000,0,0);
    drain();speculative=false;transfer=NULL;
    if(ok){capture(id,false);r->ticks++;}
    cyc_mod_isolate_end();if(!ok)failures++;
}
static int player_hook(uint16_t pc){
    (void)pc;if(!enabled||cyc_mod_isolated()||!supported())return 0;
    CycModRegs regs;cyc_mod_regs(&regs);
    unsigned caller=q(0x100|(uint8_t)(regs.s+1))|(q(0x100|(uint8_t)(regs.s+2))<<8);
    player_tick=caller>=0xdb45&&caller<0xdbef;
    if(!player_tick){collision_active=false;cyc_mod_set_ram_read_hook(NULL);return 0;}
    if(scene_ready()&&q(0x100)==14)death_mode=script_mode=false; /* main loop resumed */
    if(playing())refresh(false);
    pre_x=q(0x9e);pre_y=q(0xa1);pending=-1;ticks++;collision_active=true;cyc_mod_set_ram_read_hook(collision_read);return 0;
}
static int seam_hook(uint16_t pc){
    (void)pc;if(!enabled||cyc_mod_isolated()||active<0||area!=q(0x24))return 0;
    CycModRegs regs;cyc_mod_regs(&regs);unsigned d=regs.x,next=q(0x63);
    if(d>3||rooms[active].edges[d]!=next)return 0;
    /* The native right scroll begins when the player's right edge crosses.
     * Retain source ownership until his origin wraps; this keeps position
     * continuous instead of teleporting the 16-pixel body at x=241. */
    if(!rooms[next].live&&!initialize(next))return 0;
    pending=(int)next;direction=(int)d;pending_y=q(0xa1);p(0x63,active);p(0x54,d);return 1;
}
static bool adopt(unsigned next,int x,int y){
    uint64_t start=SDL_GetPerformanceCounter();
    capture((unsigned)active,true);load(next);
    for(unsigned i=0x900;i<0x1000;i++)cyc_mod_chr_poke((uint16_t)i,rooms[next].chr[i]);
    p(0x9e,x);p(0xa1,y);p(0x9f,0);p(0xa2,0);p(0xc,0);p(0xd,0);p(0x57,0);p(0x58,0);p(0x59,0);
    p(0x54,255);p(0xe,0);p(0xb4,0);p(0x2b3,255);
    active=(int)next;handoffs++;
    double cost=(SDL_GetPerformanceCounter()-start)*1000.0/SDL_GetPerformanceFrequency();if(cost>max_seam_ms)max_seam_ms=cost;
    return true;
}
static void sync_nametable(void){
    uint8_t nt[2048];size_t n;const uint8_t *old=cyc_ppu_ciram(&n);
    if(n!=sizeof nt){failures++;return;}memcpy(nt,old,sizeof nt);
    Room *r=&rooms[active];
    for(unsigned page=0;page<2;page++)for(unsigned by=0;by<13;by++)for(unsigned bx=0;bx<16;bx++){
        unsigned block=r->ram[0x600+by*16+bx];
        for(unsigned dy=0;dy<2;dy++)for(unsigned dx=0;dx<2;dx++){
            unsigned x=bx*2+dx,y=4+by*2+dy,ptr=word(0x80+(dy*2+dx)*2);
            nt[page*1024+y*32+x]=(uint8_t)data(3,ptr+block);
            unsigned index=page*1024+960+(y/4)*8+x/4,shift=(y&2?4:0)+(x&2?2:0);
            unsigned pal=data(3,word(0x7e)+block)&3;
            nt[index]=(uint8_t)((nt[index]&~(3u<<shift))|(pal<<shift));
        }
    }
    if(!cyc_mod_ciram_upload(0,nt,sizeof nt))failures++;
}
static int draw_hook(uint16_t pc){
    (void)pc;if(!enabled||cyc_mod_isolated()||active<0)return 0;
    cyc_mod_set_ram_read_hook(NULL);
    collision_active=false;
    if(death_mode||script_mode){pending=-1;return 0;}
    if(!player_tick||q(0x24)!=area||q(0x63)!=active){pending=-1;return 0;}
    int x=q(0x9e),y=q(0xa1),next=pending;
    if(next>=0){
        if(direction==0)x=255;
        else if(direction==1){next=-1;}
        else if(direction==2)y=(pending_y+RH)&255;
        else if(pending_y>=RH)y=pending_y-RH;
        else {p(0xa1,pending_y);next=-1;}
        p(0x54,255);p(0x9f,0);p(0xa2,0);pending=-1;
    }
    if(next<0&&pre_x>240&&x<16){next=rooms[active].edges[1];if(next==255)next=-1;}
    if(next>=0){
        uint64_t start=SDL_GetPerformanceCounter();
        if(!rooms[next].live&&!initialize((unsigned)next))return 0;adopt((unsigned)next,x,y);sync_nametable();
        double cost=(SDL_GetPerformanceCounter()-start)*1000.0/SDL_GetPerformanceFrequency();if(cost>max_seam_ms)max_seam_ms=cost;
    }
    return 0;
}
static void dimensions(int *w,int *h){
    int dw,dh;cyc_video_drawable_size(&dw,&dh);if(dw>0&&dh>0){draw_w=dw;draw_h=dh;}
    *w=fixed_w?fixed_w:clamp(draw_w/zoom,128,4096);*h=fixed_h?fixed_h:clamp(draw_h/zoom,96,2048);
}
void fax_world_step(void){
    if(!enabled||!supported())return;
    if(!trace){const char *path=getenv("NESRECOMP_WORLD_TRACE");if(path&&*path){trace=fopen(path,"w");if(trace)fprintf(trace,"cycles,area,room,x,y,scroll,ready,handoffs,failures,simulation_ms\n");}}
    if(trace)fprintf(trace,"%llu,%u,%u,%u,%u,%u,%u,%u,%u,%.4f\n",(unsigned long long)cyc_cycle_count(),q(0x24),q(0x63),q(0x9e),q(0xa1),q(0x54),q(0xe),handoffs,failures,sim_ms);
    if(!playing())return;
    memcpy(frozen_hud,cyc_frame_argb(),sizeof frozen_hud);hud_valid=true;
    uint64_t start=SDL_GetPerformanceCounter();refresh(true);if(active<0)return;
    if(ticks==last_tick)return;last_tick=ticks;
    int w,h;dimensions(&w,&h);Room *a=&rooms[active];
    for(unsigned id=0;id<counts[area];id++)if(id!=(unsigned)active&&rooms[id].owned){
        Room *r=&rooms[id];int dx=abs(r->x-a->x)*RW,dy=abs(r->y-a->y)*RH;
        if(atlas||(dx<w/2+RW&&dy<(h-HUD)/2+RH))tick_room(id);
    }
    sim_ms=(SDL_GetPerformanceCounter()-start)*1000.0/SDL_GetPerformanceFrequency();
}
static unsigned terrain(Room *r,int x,int y){
    unsigned block=r->ram[0x600+(y/16)*16+x/16],quadrant=(x&8?1:0)+(y&8?2:0);
    unsigned ptr=word(0x80+quadrant*2),tile=data(3,ptr+block);
    unsigned attr=data(3,word(0x7e)+block)&3,off=0x1000+tile*16+(y&7),shift=7-(x&7);
    unsigned v=((r->chr[off]>>shift)&1)|(((r->chr[off+8]>>shift)&1)<<1);
    return v?attr*4+v:0;
}
static void raster(unsigned id){
    Room *r=&rooms[id];if(!r->live){Room *a=&rooms[active];memcpy(r->chr,a->chr,8192);memcpy(r->palette,a->palette,32);}
    /* Background palette is global to the region, including fades. Isolated
     * NPC/actor loaders may temporarily select other palettes; those belong
     * only to their instance's sprites, never the neighboring terrain. */
    const uint8_t *pal=cyc_ppu_palette();unsigned emphasis=cyc_render_line_mask(239)&0xe9;
    if(raster_valid[id]&&!memcmp(raster_blocks[id],r->ram+0x600,256)&&!memcmp(raster_palette[id],pal,16)&&raster_palette[id][16]==emphasis&&!memcmp(raster_chr[id],r->chr+0x1000,4096))return;
    uint32_t colors[16];for(unsigned i=0;i<16;i++)colors[i]=hw_palette_argb[(pal[i]&((emphasis&1)?0x30:0x3f))|((emphasis>>5)<<6)];
    if(!(emphasis&8))for(unsigned i=1;i<16;i++)colors[i]=colors[0];
    for(int y=0;y<RH;y++)for(int x=0;x<RW;x++)rasters[id][y*RW+x]=colors[terrain(r,x,y)];
    memcpy(raster_blocks[id],r->ram+0x600,256);memcpy(raster_palette[id],pal,16);raster_palette[id][16]=(uint8_t)emphasis;memcpy(raster_chr[id],r->chr+0x1000,4096);raster_valid[id]=true;
}
static void actors(unsigned id,int w,int h){
    Room *r=&rooms[id];if(!r->live)return;
    /* Sprite palettes are global to the connected region just like terrain
     * palettes. A neighbor initialized during an arrival may have inherited
     * a building/fade palette; it must use the active scene's colors. */
    const uint8_t *pal=rooms[active].palette;
    unsigned mask=cyc_render_line_mask(239);
    int ox=r->x*RW-camera_x,oy=HUD+r->y*RH-camera_y;
    for(int s=63;s>=1;s--){const uint8_t *o=r->ram+0x700+s*4;int sy=o[0]+1,sx=o[3];
        if(sy<HUD||sy>=240)continue;
        if(id==(unsigned)active){int px=r->ram[0x9e];if(px>240&&sx<32)sx+=256;}
        unsigned tile=o[1],attr=o[2];
        for(int y=0;y<8;y++)for(int x=0;x<8;x++){
            int dx=ox+sx+x,dy=oy+sy-HUD+y;if(dx<0||dx>=w||dy<HUD||dy>=h)continue;
            unsigned py=attr&128?7-y:y,shift=attr&64?x:7-x,off=tile*16+py;
            unsigned v=((r->chr[off]>>shift)&1)|(((r->chr[off+8]>>shift)&1)<<1);if(!v)continue;
            if((attr&32)&&terrain(r,clamp(sx+x,0,255),clamp(sy-HUD+y,0,207)))continue;
            canvas[(size_t)dy*w+dx]=hw_palette_argb[(pal[16+(attr&3)*4+v]&((mask&1)?0x30:0x3f))|((mask>>5)<<6)];
        }
    }
}
/* The NES clips player tiles at its 256x240 raster even though the world
 * continues there. Ask the original drawing routines for an unclipped pose
 * at a safe scratch position, then supply just its off-room pixels. */
static void player_edge(int w,int h){
    Room *r=&rooms[active];
    int px=r->ram[0x9e],py=r->ram[0xa1];if(px>=8&&px<=232&&py>=8&&py<=176)return;
    uint8_t oam[256];if(!cyc_mod_isolate_begin())return;
    /* Use the same retained player pose during dialogue, even while native
     * portrait code temporarily changes drawing state. */
    for(unsigned i=0;i<2048;i++)p(i,r->ram[i]);
    p(0x9e,128);p(0xa1,96);p(0x9f,0);p(0xa2,0);p(0xc,0);p(0x57,0);
    bool ok=bank(14)&&call(0xcb17,0,0)&&call(0xb982,0,0)&&call(0xebee,0,0)&&call(0xb7d6,0,0);
    if(ok)for(unsigned i=0;i<256;i++)oam[i]=q(0x700+i);
    cyc_mod_isolate_end();if(!ok){failures++;return;}
    int ox=r->x*RW-camera_x,oy=HUD+r->y*RH-camera_y;
    unsigned mask=cyc_render_line_mask(239);
    for(int s=63;s>=1;s--){const uint8_t *o=oam+s*4;if(o[0]>=239)continue;
        int sx=o[3]+px-128,sy=o[0]+1-HUD+py-96;unsigned attr=o[2],tile=o[1];
        for(int y=0;y<8;y++)for(int x=0;x<8;x++){
            int lx=sx+x,ly=sy+y;if(lx>=0&&lx<RW&&ly>=0&&ly<RH)continue;
            int dx=ox+lx,dy=oy+ly;if(dx<0||dx>=w||dy<HUD||dy>=h)continue;
            unsigned cy=attr&128?7-y:y,shift=attr&64?x:7-x,off=tile*16+cy;
            unsigned v=((r->chr[off]>>shift)&1)|(((r->chr[off+8]>>shift)&1)<<1);if(!v)continue;
            canvas[(size_t)dy*w+dx]=hw_palette_argb[(r->palette[16+(attr&3)*4+v]&((mask&1)?0x30:0x3f))|((mask>>5)<<6)];
        }
    }
}
static void menu_rect(int width,int height,const uint32_t *native,int x,int y,int w,int h){
    int pw=width<RW?width:RW,ph=RH*pw/RW;
    if(ph>height-HUD){ph=height-HUD;pw=RW*ph/RH;}
    int px=(width-pw)/2;
    for(int dy=0;dy<ph;dy++)for(int dx=0;dx<pw;dx++){
        int sx=dx*RW/pw,sy=HUD+dy*RH/ph;
        if(sx>=x&&sx<x+w&&sy>=y&&sy<y+h)
            canvas[(size_t)(HUD+dy)*width+px+dx]=native[sy*RW+sx];
    }
}
static bool ui_pixel(int x,int y){
    if((!script_mode&&q(0x100)!=12)||q(0x20c))return false;
    int bx=q(0x208)*8,by=q(0x209)*8;
    if(bx==32&&by==64&&x>=16&&x<96&&y>=48&&y<160)return true;
    return x>=bx&&x<bx+q(0x20a)*8&&y>=by&&y<by+q(0x20b)*8;
}
const uint32_t *fax_world_present(int *w,int *h,const uint32_t *native){
    /* Start pauses native simulation, not the expanded picture. Select's
     * native inventory is composited over the frozen world at the same zoom.
     * Never show a cached region while an original portal is replacing it. */
    if(!enabled||!supported())return NULL;
    uint64_t start=SDL_GetPerformanceCounter();dimensions(w,h);
    bool same=active>=0&&area==q(0x24)&&active==q(0x63);
    Room *a=same?&rooms[active]:NULL;int l=0,t=0,r=0,b=0;
    if(same){l=r=a->x;t=b=a->y;
        for(unsigned i=0;i<counts[area];i++)if(rooms[i].owned){Room *v=&rooms[i];if(v->x<l)l=v->x;if(v->x>r)r=v->x;if(v->y<t)t=v->y;if(v->y>b)b=v->y;}
        if(atlas){*w=clamp((r-l+1)*RW,128,4096);*h=clamp((b-t+1)*RH+HUD,96,2048);}}
    int width=*w,height=*h;size_t n=(size_t)width*height;
    if(n>capacity){uint32_t *v=realloc(canvas,n*sizeof *v);if(!v)return NULL;canvas=v;capacity=n;}
    for(size_t i=0;i<n;i++)canvas[i]=0xff000000;
    /* Native scripts and region loaders keep their original image, inside
     * the same adaptive canvas. No frame may change the viewport to 4:3. */
    if(!same){
        int nw=width<RW?width:RW,nh=240*nw/RW;
        if(nh>height){nh=height;nw=RW*nh/240;}
        int nx=(width-nw)/2;
        for(int y=0;y<nh;y++)for(int x=0;x<nw;x++)canvas[(size_t)y*width+nx+x]=native[(y*240/nh)*RW+x*RW/nw];
        goto finished;
    }
    camera_x=atlas?l*RW:a->x*RW+a->ram[0x9e]+8-width/2;
    camera_y=atlas?t*RH:a->y*RH+a->ram[0xa1]+16-(height-HUD)/2;
    if(!atlas){
        int xmax=(r+1)*RW-width,ymax=(b+1)*RH-(height-HUD);
        camera_x=xmax<l*RW?(l*RW+xmax)/2:clamp(camera_x,l*RW,xmax);
        camera_y=ymax<t*RH?ymax:clamp(camera_y,t*RH,ymax);
    }
    for(unsigned id=0;id<counts[area];id++)if(rooms[id].owned&&rooms[id].valid){
        Room *v=&rooms[id];int ox=v->x*RW-camera_x,oy=HUD+v->y*RH-camera_y;
        if(ox>=width||ox+RW<=0||oy>=height||oy+RH<=HUD)continue;raster(id);
        int x0=ox<0?-ox:0,x1=width-ox<RW?width-ox:RW;
        for(int y=0;y<RH;y++){int dy=oy+y;if(dy<HUD||dy>=height)continue;
            memcpy(canvas+(size_t)dy*width+ox+x0,rasters[id]+y*RW+x0,(size_t)(x1-x0)*4);}
    }
    bool original_scene=death_mode;
    if(original_scene){
        int ox=a->x*RW-camera_x,oy=HUD+a->y*RH-camera_y;
        for(int y=HUD;y<240;y++)for(int x=0;x<RW;x++){
            int dx=ox+x,dy=oy+y-HUD;
            if(dx>=0&&dx<width&&dy>=HUD&&dy<height&&!ui_pixel(x,y))canvas[(size_t)dy*width+dx]=native[y*RW+x];
        }
    }else{
        for(unsigned id=0;id<counts[area];id++)if(rooms[id].owned&&id!=(unsigned)active)actors(id,width,height);
        actors((unsigned)active,width,height);player_edge(width,height);
    }
    if((script_mode||q(0x100)==12)&&!q(0x20c)){
        /* Overlay native text boxes only. Copying the entire NES image
         * would erase frozen actors inside its rectangle while leaving
         * the neighboring actors visible. Inventory submenus retain the
         * top menu underneath them. All coordinates are native tile units. */
        int x=q(0x208)*8,y=q(0x209)*8;
        if(x==32&&y==64)menu_rect(width,height,native,16,48,80,112);
        if(q(0x3c7)<128)menu_rect(width,height,native,16,112,64,80);
        menu_rect(width,height,native,x,y,q(0x20a)*8,q(0x20b)*8);
    }
    int hw=width<256?width:256,hh=HUD*hw/256,hx=(width-hw)/2;
    const uint32_t *hud=hud_valid&&!original_scene?frozen_hud:native;
    for(int y=0;y<hh;y++)for(int x=0;x<hw;x++)canvas[(size_t)y*width+hx+x]=hud[(y*HUD/hh)*256+x*256/hw];
finished:
    picture_w=width;picture_h=height;render_ms=(SDL_GetPerformanceCounter()-start)*1000.0/SDL_GetPerformanceFrequency();return canvas;
}
void fax_world_reset(void){make_mask();memset(rooms,0,sizeof rooms);memset(raster_valid,0,sizeof raster_valid);area=active=-1;pending=-1;rom_ok=false;hud_valid=death_mode=script_mode=false;ticks=last_tick=handoffs=failures=portals=0;player_tick=collision_active=false;cyc_mod_set_ram_read_hook(NULL);}
void fax_world_loaded(void){memset(raster_valid,0,sizeof raster_valid);cyc_mod_set_ram_read_hook(collision_active?collision_read:NULL);}
bool fax_world_option(const char *name,const char *value){
    if(!strcmp(name,"--world-view")){if(strcmp(value,"off")&&strcmp(value,"seamless")&&strcmp(value,"atlas"))return false;enabled=strcmp(value,"off")!=0;hooks(enabled);atlas=!strcmp(value,"atlas");if(enabled)nes_mod_set_local_only("Seamless world",1);return true;}
    if(!strcmp(name,"--world-size")){int w,h;char c;if(sscanf(value,"%dx%d%c",&w,&h,&c)!=2||w<128||w>4096||h<96||h>2048)return false;fixed_w=w;fixed_h=h;return true;}return false;
}
void fax_world_event(const void *ev){
#ifdef CYC_WITH_SDL
    const SDL_Event *e=ev;if(!enabled)return;if(e->type==SDL_MOUSEWHEEL)zoom=clamp(zoom-e->wheel.y,1,8);if(e->type==SDL_KEYDOWN&&!e->key.repeat&&e->key.keysym.sym==SDLK_F4)atlas=!atlas;
#else
    (void)ev;
#endif
}
#ifdef CYC_WITH_SDL
static void status(int id,const char *line){
    (void)line;char out[850];unsigned live=0,owned=0,actors_count=0;uint64_t sum=0;
    for(unsigned i=0;i<MAX_ROOMS;i++){Room *r=&rooms[i];owned+=r->owned;live+=r->live;sum+=r->ticks;if(r->live)for(unsigned j=0;j<8;j++)actors_count+=r->ram[0x2cc+j]<128;}
    snprintf(out,sizeof out,"\"enabled\":%s,\"area\":%d,\"room\":%d,\"owned\":%u,\"live\":%u,\"actors\":%u,\"neighbor_ticks\":%llu,\"handoffs\":%u,\"portals\":%u,\"failures\":%u,\"camera\":[%d,%d],\"size\":[%d,%d],\"simulation_ms\":%.3f,\"render_ms\":%.3f,\"max_seam_ms\":%.3f,\"playing\":%s",enabled?"true":"false",area,active,owned,live,actors_count,(unsigned long long)sum,handoffs,portals,failures,camera_x,camera_y,picture_w,picture_h,sim_ms,render_ms,max_seam_ms,playing()?"true":"false");cyc_tcp_ok(id,out);
}
static void room_status(int id,const char *line){long n=active;cyc_tcp_long(line,"room",&n);if(n<0||n>=MAX_ROOMS){cyc_tcp_err(id,"invalid room");return;}Room *r=&rooms[n];char out[512];snprintf(out,sizeof out,"\"room\":%ld,\"xy\":[%d,%d],\"edges\":[%u,%u,%u,%u],\"live\":%u,\"ticks\":%llu,\"entities\":[%u,%u,%u,%u,%u,%u,%u,%u],\"x\":[%u,%u,%u,%u,%u,%u,%u,%u]",n,r->x,r->y,r->edges[0],r->edges[1],r->edges[2],r->edges[3],r->live,(unsigned long long)r->ticks,r->ram[0x2cc],r->ram[0x2cd],r->ram[0x2ce],r->ram[0x2cf],r->ram[0x2d0],r->ram[0x2d1],r->ram[0x2d2],r->ram[0x2d3],r->ram[0xba],r->ram[0xbb],r->ram[0xbc],r->ram[0xbd],r->ram[0xbe],r->ram[0xbf],r->ram[0xc0],r->ram[0xc1]);cyc_tcp_ok(id,out);}
static void probe(int id,const char *line){
    (void)line;uint8_t *before=NULL,*after=NULL;size_t nb=0,na=0,n=0;char err[256];
    bool saved=cyc_state_save(&before,&nb,err,sizeof err);
    const uint8_t *ciram=cyc_ppu_ciram(&n);uint8_t byte=ciram[0],changed=byte^255;
    bool invalid=!cyc_mod_ciram_upload(SIZE_MAX,&changed,1)&&!cyc_mod_ciram_upload(n,&changed,1)&&!cyc_mod_ciram_upload(0,NULL,1);
    bool isolated=false;if(cyc_mod_isolate_begin()){isolated=!cyc_mod_ciram_upload(0,&changed,1);cyc_mod_isolate_end();}
    bool valid=cyc_mod_ciram_upload(0,&changed,1)&&cyc_ppu_ciram(&n)[0]==changed&&cyc_mod_ciram_upload(0,&byte,1);
    bool exact=saved&&cyc_state_save(&after,&na,err,sizeof err)&&na==nb&&!memcmp(before,after,nb);
    free(before);free(after);char out[256];snprintf(out,sizeof out,"\"invalid_inputs_rejected\":%s,\"isolated_upload_rejected\":%s,\"upload_and_restore\":%s,\"machine_state_unchanged\":%s",invalid?"true":"false",isolated?"true":"false",valid?"true":"false",exact?"true":"false");cyc_tcp_ok(id,out);
}
void fax_world_tcp_setup(void){cyc_tcp_register("fax_world","Continuous world status and component timings",status);cyc_tcp_register("fax_world_room","Persistent neighboring room state",room_status);cyc_tcp_register("fax_world_probe","CIRAM API bounds, isolation and exact machine restoration",probe);}
#else
void fax_world_tcp_setup(void){}
#endif
enum { STATE_HEADER=32 };
static int state_get(uint8_t *buf,int cap){
    if(!enabled)return 0;int len=STATE_HEADER+(int)sizeof rooms;if(len>cap)return -1;
    memset(buf,0,STATE_HEADER);memcpy(buf,"FAXWORLD",8);buf[8]=4;buf[9]=(uint8_t)(area+1);buf[10]=(uint8_t)(active+1);buf[18]=death_mode;buf[19]=script_mode;
    buf[11]=(uint8_t)(pending+1);buf[12]=(uint8_t)direction;buf[13]=player_tick;buf[14]=collision_active;buf[15]=(uint8_t)pending_y;
    buf[16]=(uint8_t)pre_x;buf[17]=(uint8_t)pre_y;memcpy(buf+20,&ticks,4);memcpy(buf+24,&last_tick,4);
    memcpy(buf+STATE_HEADER,rooms,sizeof rooms);return len;
}
static int state_validate(const uint8_t *buf,int len){
    if(!len)return 1;if(!enabled||!buf||len!=STATE_HEADER+sizeof rooms||memcmp(buf,"FAXWORLD",8)||buf[8]!=4||buf[9]>8||buf[10]>MAX_ROOMS||buf[11]>MAX_ROOMS||buf[12]>3||buf[13]>1||buf[14]>1||buf[18]>1||buf[19]>1)return 0;
    if(!buf[9]&&(buf[10]||buf[11]))return 0;
    if(buf[9]&&(buf[10]>counts[buf[9]-1]||buf[11]>counts[buf[9]-1]))return 0;
    for(unsigned i=0;i<MAX_ROOMS;i++){Room r;memcpy(&r,buf+STATE_HEADER+i*sizeof r,sizeof r);if(r.live>1||r.valid>1||r.owned>1||r.x< -83||r.x>83||r.y< -83||r.y>83)return 0;for(unsigned j=0;j<4;j++)if(r.edges[j]!=255&&r.edges[j]>=MAX_ROOMS)return 0;}return 1;
}
static int state_set(const uint8_t *buf,int len){
    if(!state_validate(buf,len))return 0;if(!len){fax_world_reset();return 1;}
    area=buf[9]-1;active=buf[10]-1;pending=buf[11]-1;direction=buf[12];player_tick=buf[13]!=0;collision_active=buf[14]!=0;death_mode=buf[18]!=0;script_mode=buf[19]!=0;pending_y=buf[15];pre_x=buf[16];pre_y=buf[17];
    memcpy(&ticks,buf+20,4);memcpy(&last_tick,buf+24,4);memcpy(rooms,buf+STATE_HEADER,sizeof rooms);fax_world_loaded();return 1;
}
static int hud_get(uint8_t *buf,int cap){
    if(!enabled||!hud_valid)return 0;
    int n=4+(int)sizeof frozen_hud;if(cap<n)return -1;
    memcpy(buf,"HUD1",4);memcpy(buf+4,frozen_hud,sizeof frozen_hud);return n;
}
static int hud_validate(const uint8_t *buf,int len){return !len||(enabled&&buf&&len==4+(int)sizeof frozen_hud&&!memcmp(buf,"HUD1",4));}
static int hud_set(const uint8_t *buf,int len){
    if(!hud_validate(buf,len))return 0;hud_valid=len!=0;
    if(hud_valid)memcpy(frozen_hud,buf+4,sizeof frozen_hud);return 1;
}
static void hooks(bool on){const char *ids[]={"player","seam","draw","queue","wait","pause","inventory","death","script"};char id[64];for(unsigned i=0;i<sizeof ids/sizeof ids[0];i++){snprintf(id,sizeof id,"faxanadu.world.%s",ids[i]);nes_mod_set_function_hook_enabled(id,on);}}
static void deactivate(void){enabled=atlas=false;fixed_w=fixed_h=0;cyc_mod_set_ram_read_hook(NULL);hooks(false);}
static void activate(void){enabled=true;hooks(true);zoom=nes_mod_get_option_int("faxanadu.enhancement.seamless-world","seamless-world","pixel-zoom",3);nes_mod_set_local_only("Seamless world",1);}
NES_MOD_CONSTRUCTOR(register_world){
    if(!nes_mod_register_function_entry_plugin("faxanadu.world.player",0xe0ca,player_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.seam",0xe8e9,seam_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.draw",0xb982,draw_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.pause",0xe02b,freeze_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.inventory",0xe016,freeze_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.death",0xd8ec,death_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.script",0x8242,script_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.queue",0xcfdc,queue_hook)||
       !nes_mod_register_function_entry_plugin("faxanadu.world.wait",0xcff4,wait_hook)||
       !nes_mod_register_reset_callback(deactivate)||!nes_mod_register_activation_plugin("faxanadu.seamless-world",activate)||
       !nes_mod_register_savestate_hook("faxanadu.world",state_get,state_set)||!nes_mod_register_savestate_validator("faxanadu.world",state_validate)||
       !nes_mod_register_savestate_hook("faxanadu.world.hud",hud_get,hud_set)||!nes_mod_register_savestate_validator("faxanadu.world.hud",hud_validate))abort();
}
