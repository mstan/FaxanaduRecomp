/*
 * Faxanadu semantic profiles for NESRecomp's opt-in voxel compositor.
 * The parked diorama remains available to developers; the visible experiment
 * uses an upright side-scroller reconstruction with the camera at the hero.
 */
#include "game_voxel.h"

#include "config.h"
#include "controller.h"
#include "nes_runtime.h"
#include "voxel_screen_profile.h"

#include <math.h>

#define FAXANADU_PI 3.14159265358979323846f
#define FAXANADU_SOURCE_Y 32

static NesVoxelScreenState s_voxel;
static const NesVoxelScreenProfile *s_active_profile;
static int s_first_person;
static int s_mod_enabled;
static float s_first_person_heading;
static float s_first_person_target_heading;
static float s_first_person_aim_pitch;
static float s_first_person_free_yaw;
static float s_right_stick_x;
static float s_right_stick_y;
static int s_first_person_heading_initialized;

static int faxanadu_scene_visible(const uint32_t *framebuffer,
                                  int stride, void *user) {
    int bright = 0;
    (void)user;
    if (!framebuffer) return 0;
    /* Dialogue boxes and title/mantra panels are authored 2D overlays. Keep
     * those screens native instead of turning their borders and letters into
     * architecture. */
    for (int y = 48; y < 176; y += 2) {
        for (int x = 16; x < 240; x += 2) {
            uint32_t color =
                framebuffer[y * stride + g_widescreen_left + x];
            unsigned sum = ((color >> 16) & 0xFFu) +
                           ((color >> 8) & 0xFFu) +
                           (color & 0xFFu);
            if (sum > 600u) bright++;
        }
    }
    return bright < 55;
}

static float faxanadu_diorama_tile_height(
    const NesVoxelScreenSample *sample, void *user) {
    int filled = sample->non_background_pixels;
    (void)user;
    if (filled < 7) return 0.0f;
    if (filled >= 42) return 17.0f;
    if (filled >= 24) return 11.0f;
    return 4.0f;
}

static float faxanadu_first_person_tile_height(
    const NesVoxelScreenSample *sample, void *user) {
    int filled = sample->non_background_pixels;
    (void)user;
    /* Side-layout depth is binary at render time. Require substantial tile
     * coverage so thin vines, signs, ladders, and background linework remain
     * visible in the texture without becoming walls across the player's view. */
    if (filled < 42) return 0.0f;
    return 16.0f;
}

static float clamp_float(float value, float low, float high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

static float ease_heading(float current, float target) {
    float delta = target - current;
    while (delta > 180.0f) delta -= 360.0f;
    while (delta < -180.0f) delta += 360.0f;
    if (delta > -0.25f && delta < 0.25f) return target;
    current += delta * 0.38f;
    while (current > 180.0f) current -= 360.0f;
    while (current < -180.0f) current += 360.0f;
    return current;
}

static void faxanadu_first_person_camera(
    NesVoxelScreenCamera *camera,
    float pitch, float yaw, float roll,
    float zoom_percent, void *user) {
    float player_x = (float)g_ram[0x003C] + 8.0f;
    float player_y = (float)g_ram[0x003D];
    uint8_t directions = g_controller1_buttons & 0x0Fu;
    float heading;
    float look_pitch;
    float look_distance = 128.0f;
    float target_aim_pitch;
    (void)roll;
    (void)user;

    if (player_x < 8.0f || player_x > 248.0f) player_x = 64.0f;
    if (player_y < 32.0f || player_y > 232.0f) player_y = 176.0f;

    if (!s_first_person_heading_initialized) {
        /* Faxanadu begins by progressing right. Subsequent native Left/Right
         * input owns presentation facing immediately. */
        s_first_person_heading = 0.0f;
        s_first_person_target_heading = 0.0f;
        s_first_person_heading_initialized = 1;
    }
    if ((directions & 0x02u) && !(directions & 0x01u))
        s_first_person_target_heading = 180.0f;
    else if ((directions & 0x01u) && !(directions & 0x02u))
        s_first_person_target_heading = 0.0f;
    s_first_person_heading = ease_heading(
        s_first_person_heading, s_first_person_target_heading);

    /* Match SMB's comfortable head-look model: the right stick offsets the
     * native facing and recenters when released. */
    s_first_person_free_yaw +=
        ((fabsf(s_right_stick_x) > 0.18f
              ? s_right_stick_x * 75.0f : 0.0f) -
         s_first_person_free_yaw) * 0.24f;
    if (s_right_stick_y < -0.18f)
        target_aim_pitch =
            80.0f * (-s_right_stick_y - 0.18f) / 0.82f;
    else if (s_right_stick_y > 0.18f)
        target_aim_pitch =
            -35.0f * (s_right_stick_y - 0.18f) / 0.82f;
    else
        target_aim_pitch = 0.0f;
    s_first_person_aim_pitch +=
        (target_aim_pitch - s_first_person_aim_pitch) * 0.30f;

    heading =
        (s_first_person_heading + yaw + s_first_person_free_yaw) *
        FAXANADU_PI / 180.0f;
    look_pitch =
        ((pitch - 15.0f) + s_first_person_aim_pitch) *
        FAXANADU_PI / 180.0f;

    camera->enabled = 1;
    camera->eye_x = player_x + cosf(heading) * 4.0f;
    camera->eye_y = clamp_float(
        (float)(FAXANADU_SOURCE_Y + 208) - player_y - 10.0f,
        10.0f, 198.0f);
    camera->eye_z = 0.0f;
    camera->look_at_x =
        camera->eye_x + cosf(heading) * cosf(look_pitch) * look_distance;
    camera->look_at_y =
        camera->eye_y + sinf(look_pitch) * look_distance;
    camera->look_at_z =
        camera->eye_z + sinf(heading) * cosf(look_pitch) * look_distance;
    camera->focal_scale = clamp_float(
        (0.74f - 0.14f *
            clamp_float(s_first_person_aim_pitch / 80.0f, 0.0f, 1.0f)) *
            zoom_percent / 100.0f,
        0.40f, 1.30f);
    camera->center_y = 0.56f;
}

static int faxanadu_first_person_sprite_visible(
    int min_x, int min_y, int max_x, int max_y, void *user) {
    int player_x = g_ram[0x003C];
    int player_y = g_ram[0x003D];
    (void)user;
    /* The camera occupies the hero's 16x32 metasprite. Enemies, spells,
     * pickups, and effects remain camera-facing world cards. */
    if (max_x >= player_x - 3 && min_x <= player_x + 19 &&
        max_y >= player_y - 3 && min_y <= player_y + 35)
        return 0;
    return 1;
}

static int faxanadu_grid_offset(void *user) {
    (void)user;
    return -(g_ppuscroll_x & 15);
}

static const NesVoxelScreenProfile s_diorama_profile = {
    "Faxanadu diorama",
    32, 208, 32, 0, 85,
    30, -20, 0, 100, 125,
    0xFF06100Au, 0xFF183018u,
    faxanadu_scene_visible,
    faxanadu_diorama_tile_height,
    0
};

static const NesVoxelScreenProfile s_first_person_profile = {
    "Faxanadu first-person voxel",
    32, 208, 32, 0, 85,
    15, 0, 0, 100, 120,
    0xFF06100Au, 0xFF183018u,
    faxanadu_scene_visible,
    faxanadu_first_person_tile_height,
    0,
    faxanadu_first_person_camera,
    faxanadu_first_person_sprite_visible,
    NES_VOXEL_LAYOUT_SIDE,
    2,
    faxanadu_grid_offset,
    16
};

void game_voxel_set_mod_enabled(int enabled) {
    s_mod_enabled = enabled != 0;
    nes_voxel_screen_set_enabled(&s_voxel, enabled);
}

void game_voxel_configure_mod(int first_person,
                              int pitch, int yaw, int roll,
                              int zoom_percent, int sprite_scale_percent) {
    s_first_person = first_person != 0;
    s_active_profile =
        s_first_person ? &s_first_person_profile : &s_diorama_profile;
    s_first_person_heading_initialized = 0;
    s_first_person_aim_pitch = 0.0f;
    s_first_person_free_yaw = 0.0f;
    s_right_stick_x = s_right_stick_y = 0.0f;
    nes_voxel_screen_configure(&s_voxel, pitch, yaw, roll,
                               zoom_percent, sprite_scale_percent);
}

void game_voxel_handle_event(const SDL_Event *event) {
    if (s_mod_enabled && s_first_person && event &&
        event->type == SDL_CONTROLLERAXISMOTION &&
        g_nes_config.player_src[0] == 2 &&
        controller_instance_is_player(event->caxis.which, 1)) {
        float value = event->caxis.value < 0
            ? (float)event->caxis.value / 32768.0f
            : (float)event->caxis.value / 32767.0f;
        if (event->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
            s_right_stick_x = value;
        else if (event->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
            s_right_stick_y = value;
    } else if (event &&
               event->type == SDL_CONTROLLERDEVICEREMOVED) {
        s_right_stick_x = s_right_stick_y = 0.0f;
    }
    nes_voxel_screen_handle_event(&s_voxel, event);
}

void game_voxel_init(void) {
    if (!s_active_profile)
        s_active_profile = &s_diorama_profile;
    nes_voxel_screen_init(&s_voxel, s_active_profile);
}

void game_voxel_update(void) {
    if (!s_active_profile)
        s_active_profile = &s_diorama_profile;
    nes_voxel_screen_update(&s_voxel, s_active_profile);
}

void game_voxel_post_render(uint32_t *framebuffer) {
    NesVoxelScreenProfile scene_profile;
    uint32_t background;
    if (!s_active_profile)
        s_active_profile = &s_diorama_profile;
    scene_profile = *s_active_profile;
    background = g_nes_palette[g_ppu_pal[0] & 0x3Fu];
    /* Preserve each room's real palette instead of imposing a single outdoor
     * gradient on towns, interiors, mist, and late-game areas. */
    scene_profile.sky_top = background;
    scene_profile.sky_bottom = background;
    nes_voxel_screen_post_render(&s_voxel, &scene_profile, framebuffer);
}
