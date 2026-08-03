cmake_minimum_required(VERSION 3.20)
project(FaxanaduRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)

# nesrecomp/ and recomp-ui/ are git submodules (see .gitmodules); the pinned
# commit is the gitlink recorded in this repo. After cloning run setup.sh/.bat
# (git submodule update --init) to fetch them at the recorded commits.

set(NESRECOMP_ENABLE_MODS ON CACHE BOOL
    "Enable package mods for Faxanadu" FORCE)
include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

# ---- Main executable ----
add_executable(FaxanaduRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    extras.c
    game_voxel.c
    mods/voxel_plugin.c
    override_text.c   # optional text override plugin — game-specific strings in extras.c
    ${NESRECOMP_RUNNER_ROOT}/src/override_chr.c   # CHR asset dump + override plugin
    ${NESRECOMP_RUNNER_ROOT}/src/chr_codec.c       # NES 2bpp CHR <-> PNG codec
    nes_snapshot.c
    verify_mode.c
    watchdog.c
    generated/faxanadu_full.c
    generated/faxanadu_dispatch.c
)

target_compile_definitions(FaxanaduRecomp PRIVATE
    RECOMP_STACK_TRACKING
    WATCHDOG_ENABLED
    NESRECOMP_GAME_ID="faxanadu-us"
    NESRECOMP_GAME_ROM_CRC32="57dd23d1"
    NESRECOMP_GAME_SDL_EVENT_HOOK=game_voxel_handle_event)

target_include_directories(FaxanaduRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${NESRECOMP_RUNNER_ROOT}/src          # for chr_codec.h, stb_image.h
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(FaxanaduRecomp PRIVATE ${SDL2_LIBRARIES})

if(WIN32)
    target_link_libraries(FaxanaduRecomp PRIVATE ws2_32)
endif()

# ---- Post-build ----
if(WIN32)
    add_custom_command(TARGET FaxanaduRecomp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${NESRECOMP_ROOT}/runner/external/SDL2/lib/x64/SDL2.dll"
            "$<TARGET_FILE_DIR:FaxanaduRecomp>"
    )
endif()

if(MSVC)
    target_compile_options(FaxanaduRecomp PRIVATE /W3 /WX-)
    target_compile_options(FaxanaduRecomp PRIVATE /wd4102)
endif()

# ---- Pre-boot GUI launcher (recomp-ui / Dear ImGui) ----
# recomp-ui/ is a directory junction -> the shared recomp-ui checkout. Its
# module defines RECOMP_LAUNCHER on the target, un-gating the launcher block in
# launcher.c's main(), and stages the launcher assets next to the exe.
include(${CMAKE_SOURCE_DIR}/recomp-ui/recomp_ui.cmake)
recomp_target_launcher_ui(FaxanaduRecomp
    CONSOLE nes
    BOXART ${CMAKE_SOURCE_DIR}/boxart.tga)

add_custom_command(TARGET FaxanaduRecomp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/mods/preloaded"
        "$<TARGET_FILE_DIR:FaxanaduRecomp>/mods"
    COMMENT "Staging Faxanadu's preloaded NES mod packages")

# Faxanadu saves via a password (mantra), not battery SRAM. Drive the launcher's
# SAVES panel to show/edit that password (the faxanadu.srm sidecar next to the exe
# that the runtime auto-prefill reads/writes) instead of the binary SRAM UI.
target_compile_definitions(FaxanaduRecomp PRIVATE
    NESRECOMP_GAME_PASSWORD_SAVE="faxanadu.srm"
    NESRECOMP_GAME_PASSWORD_SAVE_LABEL="Mantra")

# Single-player (one controller) — hide the launcher's Player 2 card.
target_compile_definitions(FaxanaduRecomp PRIVATE NESRECOMP_GAME_PLAYERS=1)
