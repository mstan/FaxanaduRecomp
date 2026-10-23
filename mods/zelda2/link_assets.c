/* Owner-ROM assets are read only after the package runtime verifies identity.
 * No CHR, display table or audio table is distributed with this mod. */
#include "fax_link.h"
#include "fax_profile.h"
#include "cyc_mod.h"
#include "cyc_core.h"
#include "hw_internal.h"
#include "mod_audio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static uint8_t chr[8192],body[114],frames[20],palettes[16],sound[0xef],sword[16];
static NESModAudioClip clips[5];
static int ready;
static int extract(FILE *f,long base,long offset,void *out,size_t count) {
    return !fseek(f,base+offset,SEEK_SET)&&fread(out,1,count,f)==count;
}
static int build_audio(void) {
    for(int c=1;c<=2;c++) {
        int ticks=c==1?15:59,n=ticks*735;int16_t *pcm=malloc(n*sizeof *pcm);if(!pcm)return 0;
        double phase=0;unsigned lfsr=1;int pos=0;
        static const unsigned noise_period[]={4,8,16,32,64,96,128,160,202,254,380,508,762,1016,2034,4068};
        for(int tick=ticks;tick>0;tick--) {
            int timer,control;
            if(c==1){control=sword[tick];timer=noise_period[((control&15)-2)&15];}
            else {
                unsigned seq=(unsigned)tick>>2,note=seq&1?0x54:0x62;
                control=sound[seq];timer=sound[0x8c+note]|((sound[0x8b+note]&7)<<8);
            }
            for(int i=0;i<735;i++) {
                double sample;
                if(c==1) {
                    phase+=1789773.0/44100/timer;
                    while(phase>=1){unsigned bit=(lfsr^(lfsr>>1))&1;lfsr=(lfsr>>1)|(bit<<14);phase-=1;}
                    sample=(lfsr&1?-1:1)*((control>>4)&15)/15.0;
                } else {
                    double duty=((control>>6)&3)==1?.25:.5;
                    phase+=1789773.0/(16*(timer+1)*44100);phase-=floor(phase);
                    sample=(phase<duty?1:-1)*(control&15)/15.0;
                    if(i==366||i==734){timer-= (timer>>2)+1;if(timer<8)timer=8;}
                }
                pcm[pos++]=(int16_t)(sample*6500);
            }
        }
        if(clips[c])nes_mod_audio_unregister(clips[c]);
        clips[c]=nes_mod_audio_register_pcm_s16_mono(pcm,n);free(pcm);if(!clips[c])return 0;
    }
    return 1;
}
int fax_link_load_assets(const char *path) {
    ready=0;FILE *f=fopen(path,"rb");if(!f)return 0;
    fseek(f,0,SEEK_END);long size=ftell(f),base=size==262160?16:0;
    if(size!=262144&&size!=262160){fclose(f);return 0;}
    int ok=extract(f,base,0x20000,chr,sizeof chr)&&extract(f,base,0x1eb25,body,sizeof body)&&
           extract(f,base,0x1eb97,frames,sizeof frames)&&extract(f,base,0x1c46b,palettes,4)&&
           extract(f,base,0x1c477,palettes+4,4)&&extract(f,base,0x1c467,palettes+8,4)&&
           extract(f,base,0x1c463,palettes+12,4)&&
           extract(f,base,0x19104,sound,sizeof sound)&&extract(f,base,0x190e8,sword,sizeof sword);
    fclose(f);ready=ok&&build_audio();return ready;
}
void fax_link_audio_cue(unsigned cue) {
    if(!ready)return;
    if(cue==3)cue=2; /* Both sword fire and spell casting use the source pulse effect. */
    if(cue<5&&clips[cue])nes_mod_audio_play(clips[cue],72);
}
void fax_link_audio_mix(int16_t *samples,size_t count) {
    if(fax_link_active())nes_mod_audio_mix(samples,(int)count);
}
static void pixel(uint32_t *fb,int x,int y,uint32_t color,int behind) {
    if(fax_link.dying&&((y-fax_link.draw_y)&7)<fax_link.death_phase)return;
    if(x>=0&&x<256&&y>=32&&y<240&&(!behind||!cyc_frame_bg_opaque()[y*256+x]))fb[y*256+x]=color;
}
static void tile(uint32_t *fb,int number,int x,int y,int flip,int vflip,const uint8_t *palette,int behind) {
    int top=(number&1)*0x100+(number&0xfe);
    for(int row=0;row<16;row++)for(int col=0;col<8;col++) {
        int sy=vflip?15-row:row,sx=flip?col:7-col;
        const uint8_t *p=chr+(top+sy/8)*16;
        int value=((p[sy&7]>>sx)&1)|(((p[(sy&7)+8]>>sx)&1)<<1);
        if(value)pixel(fb,x+col,y+row,hw_palette_argb[palette[value]&63],behind);
    }
}
static void character(uint32_t *fb,int x,int y,int left,unsigned frame,int behind) {
    if(!ready)return;if(frame>=20)frame=0;unsigned offset=frames[frame];
    const uint8_t *palette=palettes+((fax_link.effects&(1u<<LINK_SHIELD))?4:0);
    if(frame==14) {
        static const uint8_t bob[]={1,2,3,4,3,2,1,0};
        tile(fb,0x68+((fax_link.ticks&4)?2:0),x+8,y+8+bob[(fax_link.ticks>>3)&7],0,0,palettes+4,behind);return;
    }
    /* Source tables face left. The body and blade have opposite tile flips. */
    int mirror=!left;
    for(int row=0;row<2;row++)for(int col=0;col<3;col++) {
        unsigned at=offset+row*3+(mirror?2-col:col);
        if(at<sizeof body&&body[at]!=0xf5)tile(fb,body[at],x+col*8,y+row*16,mirror,0,palette,behind);
    }
    if(frame==4||frame==5||frame==7)tile(fb,frame==7?0x54:0x32,x+(left?-8:24),y+(frame==7?16:0),!left,0,palette,behind);
}
/* Small, implementation-owned 5x7 font, rows packed into five columns. */
static const uint8_t font[37][5]={
 {126,9,9,9,126},{127,73,73,73,54},{62,65,65,65,34},{127,65,65,34,28},
 {127,73,73,73,65},{127,9,9,9,1},{62,65,73,73,122},{127,8,8,8,127},
 {0,65,127,65,0},{32,64,65,63,1},{127,8,20,34,65},{127,64,64,64,64},
 {127,2,12,2,127},{127,4,8,16,127},{62,65,65,65,62},{127,9,9,9,6},
 {62,65,81,33,94},{127,9,25,41,70},{70,73,73,73,49},{1,1,127,1,1},
 {63,64,64,64,63},{31,32,64,32,31},{63,64,56,64,63},{99,20,8,20,99},
 {7,8,112,8,7},{97,81,73,69,67},{62,81,73,69,62},{0,66,127,64,0},
 {98,81,73,73,70},{34,65,73,73,54},{24,20,18,127,16},{39,69,69,69,57},
 {60,74,73,73,48},{1,113,9,5,3},{54,73,73,73,54},{6,73,73,41,30},
 {0,0,36,0,0}};
static void text(uint32_t *fb,int x,int y,const char *s,uint32_t color) {
    for(;*s;s++,x+=6) {
        unsigned char c=(unsigned char)*s;if(c>='a'&&c<='z')c-=32;
        int n=c>='A'&&c<='Z'?c-'A':c>='0'&&c<='9'?c-'0'+26:c==':'?36:-1;
        if(n<0)continue;
        for(int col=0;col<5;col++)for(int row=0;row<7;row++)
            if((font[n][col]>>row)&1)if(x+col>=0&&x+col<256&&y+row>=0&&y+row<240)fb[(y+row)*256+x+col]=color;
    }
}
static void rect(uint32_t *fb,int x,int y,int w,int h,uint32_t color) {
    for(int yy=y;yy<y+h;yy++)for(int xx=x;xx<x+w;xx++)fb[yy*256+xx]=color;
}
void fax_link_render(uint32_t *fb) {
    if(fax_link.draw)character(fb,fax_link.draw_x-4,fax_link.draw_y,fax_link.draw_left,fax_link.draw_frame,fax_link.draw_behind);
    for(int i=0;i<LINK_PROJECTILES;i++) {
        const LinkProjectile *p=&fax_link.projectile[i];if(!p->life)continue;
        tile(fb,p->kind==1?0x32:0x64,p->x/256,p->y/256+28,p->vx>0,0,palettes+(fax_link.ticks&3)*4,0);
    }
    for(int i=0;i<8;i++)if(fax_link.transformed&(1u<<i)) {
        int x=cyc_mod_peek(F_CurrentSprites_XPos_Full+i),y=cyc_mod_peek(F_CurrentSprites_YPos+i);
        character(fb,x-4,y+32,0,14,0);
    }
    if(fax_link.flash)for(int y=32;y<240;y++)for(int x=0;x<256;x++)if((x+y)&1)fb[y*256+x]=0xffe0e8f0;
    if(!fax_link.hud_visible&&!fax_link.picker)return;
    char label[64];snprintf(label,sizeof label,"%s %u",link_spell_name(fax_link.spell),link_spell_cost(fax_link.spell,80));
    rect(fb,152,23,104,9,0xff101820);text(fb,154,24,label,0xffe8f0e0);
    if(fax_link.picker) {
        rect(fb,28,43,200,184,0xffd8d8b0);rect(fb,30,45,196,180,0xff102820);
        text(fb,50,52,"LINK MAGIC",0xfff0e8a0);
        for(unsigned i=0;i<8;i++) {
            uint32_t color=cyc_mod_peek(F_Player_MP)>=link_spell_cost(i,80)?0xffe8f0e0:0xff808880;
            if(i==fax_link.cursor){rect(fb,36,68+i*16,184,14,0xff406840);color=0xffffffff;}
            snprintf(label,sizeof label,"%s",link_spell_name(i));text(fb,44,72+i*16,label,color);
            snprintf(label,sizeof label,"%u MP",link_spell_cost(i,80));text(fb,180,72+i*16,label,color);
        }
        text(fb,40,202,"A SELECT  B CANCEL",0xffe8e0a0);text(fb,40,214,"UP B CAST",0xffe8e0a0);
    }
}
