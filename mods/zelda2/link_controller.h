#pragma once
#include "foreign_controller.h"
#include <stdint.h>

#define LINK_CONTROLLER_ID "faxanadu.zelda2.link"
enum { LINK_STAND=200, LINK_WALK, LINK_CROUCH, LINK_AIR, LINK_SLASH,
       LINK_CROUCH_SLASH, LINK_UPSTAB, LINK_DOWNSTAB, LINK_FAIRY };
enum { LINK_SHIELD, LINK_JUMP, LINK_LIFE, LINK_FAIRY_SPELL, LINK_FIRE,
       LINK_REFLECT, LINK_SPELL, LINK_THUNDER, LINK_SPELL_COUNT };
enum { LINK_BEAM=0x5a020001, LINK_FIREBALL };
typedef struct {
    int16_t speed;             /* signed source $70, sixteenths of a pixel */
    int8_t vertical;           /* source $057d: whole pixels per tick */
    uint8_t gravity_fraction;  /* source $03e6: gravity accumulator, NOT Y */
    uint8_t slash_phase, slash_timer, crouched_slash, last_attack;
    uint8_t effects, full_health, beam_live, jump_started;
    uint8_t motion_direction;
    uint8_t walk_timer,walk_frame;
} LinkPrivate;
int link_controller_register(void);
const LinkPrivate *link_private(void);
int link_private_validate(const LinkPrivate *state);
int link_restore(const ForeignState *state,const LinkPrivate *private_state);
void link_environment(uint8_t effects, int full_health, int beam_live);
void link_bounce(void);
void link_upstab_contact(void);
unsigned link_frame(void);
unsigned link_spell_cost(unsigned spell, unsigned max_mp);
const char *link_spell_name(unsigned spell);
