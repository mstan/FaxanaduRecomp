/*
 * Faxanadu semantic profile for NESRecomp's opt-in screen diorama.
 * Dense architecture receives depth, thin façade detail stays shallow, and
 * characters remain oriented sprite cards.
 */
#include "game_voxel.h"

#include "nes_runtime.h"
#include "voxel_screen_profile.h"

static NesVoxelScreenState s_voxel;

static int faxanadu_scene_visible(const uint32_t *framebuffer,
                                  int stride, void *user) {
    int bright = 0;
    (void)user;
    /* Dialogue boxes and title/mantra panels are authored 2D overlays. Keep
     * those screens native instead of turning their borders and letters into
     * architecture. */
    for (int y = 48; y < 176; y += 2) {
        for (int x = 16; x < 240; x += 2) {
            uint32_t color = framebuffer[y * stride + g_widescreen_left + x];
            unsigned sum = ((color >> 16) & 0xFFu) +
                           ((color >> 8) & 0xFFu) +
                           (color & 0xFFu);
            if (sum > 600u) bright++;
        }
    }
    return bright < 55;
}

static float faxanadu_tile_height(const NesVoxelScreenSample *sample,
                                  void *user) {
    int filled = sample->non_background_pixels;
    (void)user;
    if (filled < 7) return 0.0f;
    if (filled >= 42) return 17.0f;
    if (filled >= 24) return 11.0f;
    /* Ladders, windows, signs, and façade linework get shallow relief rather
     * than the full depth reserved for walls, floors, and platforms. */
    return 4.0f;
}

static const NesVoxelScreenProfile s_profile = {
    "Faxanadu diorama",
    32, 208, 32, 0, 85,
    30, -20, 0, 100, 125,
    0xFF06100Au, 0xFF183018u,
    faxanadu_scene_visible,
    faxanadu_tile_height,
    0
};

void game_voxel_set_mod_enabled(int enabled) {
    nes_voxel_screen_set_enabled(&s_voxel, enabled);
}

void game_voxel_configure_mod(int pitch, int yaw, int roll,
                              int zoom_percent, int sprite_scale_percent) {
    nes_voxel_screen_configure(&s_voxel, pitch, yaw, roll,
                               zoom_percent, sprite_scale_percent);
}

void game_voxel_handle_event(const SDL_Event *event) {
    nes_voxel_screen_handle_event(&s_voxel, event);
}

void game_voxel_init(void) {
    nes_voxel_screen_init(&s_voxel, &s_profile);
}

void game_voxel_update(void) {
    nes_voxel_screen_update(&s_voxel, &s_profile);
}

void game_voxel_post_render(uint32_t *framebuffer) {
    nes_voxel_screen_post_render(&s_voxel, &s_profile, framebuffer);
}
