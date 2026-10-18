cmake_minimum_required(VERSION 3.20)
project(FaxanaduRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/nesrecomp" CACHE PATH "NESRecomp engine checkout")

# nesrecomp/ and recomp-ui/ are git submodules (see .gitmodules); the pinned
# commit is the gitlink recorded in this repo. After cloning run setup.sh/.bat
# (git submodule update --init) to fetch them at the recorded commits.

set(NESRECOMP_BACKEND "cycle" CACHE STRING "CPU backend: cycle or legacy")
set_property(CACHE NESRECOMP_BACKEND PROPERTY STRINGS cycle legacy)
if(NESRECOMP_BACKEND STREQUAL "cycle")
    set(NESRECOMP_ROM "" CACHE FILEPATH "Original ROM image (not distributed)")
    set(NESRECOMP_CYCLE_SEEDS "${CMAKE_CURRENT_SOURCE_DIR}/cyc_seeds.txt" CACHE FILEPATH "Cycle coverage seeds")
    set(NESRECOMP_HOST_COMPILER "" CACHE FILEPATH "Optional prebuilt host compiler")
    if(NOT EXISTS "${NESRECOMP_ROM}")
        message(FATAL_ERROR "Set NESRECOMP_ROM to the original Faxanadu ROM")
    endif()
    find_package(Python3 3.11 REQUIRED COMPONENTS Interpreter)
    execute_process(COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tools/verify_usa_rom.py"
        --rom "${NESRECOMP_ROM}" --crc 57DD23D1 --mapper 1 --title "Faxanadu"
        RESULT_VARIABLE _usa_rom_result)
    if(NOT _usa_rom_result EQUAL 0)
        message(FATAL_ERROR "The North American ROM profile is required for this build")
    endif()
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/verify_usa_rom.py" "${NESRECOMP_ROM}")
    include("${NESRECOMP_ROOT}/runner/cyc/project.cmake")
    nesrecomp_add_cycle_game(FaxanaduRecomp
        ROM "${NESRECOMP_ROM}"
        GAME_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/game.toml"
        RECOMPILER "${NESRECOMP_HOST_COMPILER}"
        SEED_FILE "${NESRECOMP_CYCLE_SEEDS}"
        HOST_EXTRAS "${CMAKE_CURRENT_SOURCE_DIR}/cyc_extras.c"
        PLAYERS 1 REGION NTSC PASSWORD_SAVE "faxanadu.srm" PASSWORD_SAVE_LABEL "Mantra"
        BOXART "${CMAKE_CURRENT_SOURCE_DIR}/boxart.tga")
    target_sources(FaxanaduRecomp PRIVATE override_text.c
        "${NESRECOMP_ROOT}/runner/src/override_chr.c"
        "${NESRECOMP_ROOT}/runner/src/chr_codec.c"
        "${NESRECOMP_ROOT}/runner/src/crc32.c")
    target_include_directories(FaxanaduRecomp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${NESRECOMP_ROOT}/runner/include" "${NESRECOMP_ROOT}/runner/src")
    target_compile_definitions(FaxanaduRecomp PRIVATE CYC_CONTENT_TOOLS)
    return()
elseif(NOT NESRECOMP_BACKEND STREQUAL "legacy")
    message(FATAL_ERROR "NESRECOMP_BACKEND must be cycle or legacy")
endif()

include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

# ---- Main executable ----
add_executable(FaxanaduRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    extras.c
    override_text.c   # optional text override plugin — game-specific strings in extras.c
    ${NESRECOMP_RUNNER_ROOT}/src/override_chr.c   # CHR asset dump + override plugin
    ${NESRECOMP_RUNNER_ROOT}/src/chr_codec.c       # NES 2bpp CHR <-> PNG codec
    nes_snapshot.c
    verify_mode.c
    watchdog.c
    generated/faxanadu_full.c
    generated/faxanadu_dispatch.c
)

target_compile_definitions(FaxanaduRecomp PRIVATE RECOMP_STACK_TRACKING WATCHDOG_ENABLED)

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
set(NESRECOMP_RECOMP_UI "${CMAKE_CURRENT_SOURCE_DIR}/recomp-ui" CACHE PATH "recomp-ui checkout")
include("${NESRECOMP_RECOMP_UI}/recomp_ui.cmake")
recomp_target_launcher_ui(FaxanaduRecomp CONSOLE nes BOXART ${CMAKE_SOURCE_DIR}/boxart.tga)

# Faxanadu saves via a password (mantra), not battery SRAM. Drive the launcher's
# SAVES panel to show/edit that password (the faxanadu.srm sidecar next to the exe
# that the runtime auto-prefill reads/writes) instead of the binary SRAM UI.
target_compile_definitions(FaxanaduRecomp PRIVATE
    NESRECOMP_GAME_PASSWORD_SAVE="faxanadu.srm"
    NESRECOMP_GAME_PASSWORD_SAVE_LABEL="Mantra")

# Single-player (one controller) — hide the launcher's Player 2 card.
target_compile_definitions(FaxanaduRecomp PRIVATE NESRECOMP_GAME_PLAYERS=1)
