#pragma once
#include "link_controller.h"
#include <stddef.h>
#define LINK_PACKAGE "faxanadu.gameplay.zelda2-link"
#define LINK_FEATURE "play-as-link"
#define LINK_PROJECTILES 4
typedef struct {int32_t x,y,vx;uint16_t life;uint8_t kind,hit;} LinkProjectile;
typedef struct {
    uint32_t version;
    uint64_t ticks;
    uint8_t effects,spell,picker,cursor,foreign,area,screen,initialized;
    uint8_t transformed,ladder_jump,thunder,fairy_pending_end,draw,draw_frame,draw_left,draw_behind;
    uint8_t previous_draw,shortcut_picker,shortcut_cast,flash,hud_visible;
    uint8_t raw_buttons,raw_changed,dying,death_phase;
    int16_t draw_x,draw_y;
    LinkProjectile projectile[LINK_PROJECTILES];
    ForeignCollisionResult collision;
} FaxLinkState;
extern FaxLinkState fax_link;
int fax_link_active(void);
void fax_link_power_on(void);
void fax_link_frame_begin(void);
void fax_link_frame_end(void);
const uint32_t *fax_link_present(int *w,int *h);
int fax_link_load_assets(const char *path);
void fax_link_render(uint32_t *out);
void fax_link_audio_mix(int16_t *samples,size_t count);
void fax_link_audio_cue(unsigned cue);
void fax_link_event(const void *event);
int fax_link_load_setting(const char *key,const char *value);
void fax_link_save_settings(void *file);
void fax_link_tcp_setup(void);
