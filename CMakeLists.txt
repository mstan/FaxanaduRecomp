cmake_minimum_required(VERSION 3.20)
project(FaxanaduRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)

# ---- Nestopia Oracle (optional, must be set before runner.cmake) ----
option(ENABLE_NESTOPIA_ORACLE "Build with Nestopia emulator oracle for verify mode" ON)
set(NESTOPIA_DIR "${CMAKE_SOURCE_DIR}/nestopia-core")

# ---- nesrecomp pin check ----
# nesrecomp/ is a Windows directory junction → F:/Projects/nesrecomp.
# nesrecomp.pin records the expected nesrecomp version. Two optional fields:
#   branch = <ref>   default origin/master, used when sha is unset
#   sha    = <sha>   exact pin, takes precedence over branch when set
# At configure time we resolve the expected SHA, compare to HEAD of the
# junction target, and fail with a clear error on drift.
if(EXISTS "${CMAKE_SOURCE_DIR}/nesrecomp.pin")
    file(STRINGS "${CMAKE_SOURCE_DIR}/nesrecomp.pin" _PIN_LINES)
    set(NESRECOMP_PIN_BRANCH "")
    set(NESRECOMP_PIN_SHA "")
    foreach(_line IN LISTS _PIN_LINES)
        if(_line MATCHES "^[ \t]*#")
            # comment, skip
        elseif(_line MATCHES "^[ \t]*branch[ \t]*=[ \t]*(.*)$")
            string(STRIP "${CMAKE_MATCH_1}" NESRECOMP_PIN_BRANCH)
        elseif(_line MATCHES "^[ \t]*sha[ \t]*=[ \t]*(.*)$")
            string(STRIP "${CMAKE_MATCH_1}" NESRECOMP_PIN_SHA)
        endif()
    endforeach()

    if(NESRECOMP_PIN_SHA)
        set(NESRECOMP_EXPECTED_SHA "${NESRECOMP_PIN_SHA}")
        set(NESRECOMP_PIN_SOURCE "explicit sha in nesrecomp.pin")
    else()
        if(NOT NESRECOMP_PIN_BRANCH)
            set(NESRECOMP_PIN_BRANCH "origin/master")
        endif()
        execute_process(
            COMMAND git -C "${NESRECOMP_ROOT}" rev-parse "${NESRECOMP_PIN_BRANCH}"
            OUTPUT_VARIABLE NESRECOMP_EXPECTED_SHA
            OUTPUT_STRIP_TRAILING_WHITESPACE
            RESULT_VARIABLE _NESRECOMP_RP_RC
        )
        if(NOT _NESRECOMP_RP_RC EQUAL 0)
            message(FATAL_ERROR
                "nesrecomp pin: failed to resolve branch '${NESRECOMP_PIN_BRANCH}' "
                "in ${NESRECOMP_ROOT}. Is the ref fetched?")
        endif()
        set(NESRECOMP_PIN_SOURCE "tip of ${NESRECOMP_PIN_BRANCH}")
    endif()

    execute_process(
        COMMAND git -C "${NESRECOMP_ROOT}" rev-parse HEAD
        OUTPUT_VARIABLE NESRECOMP_ACTUAL_SHA
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE _NESRECOMP_HEAD_RC
    )
    if(NOT _NESRECOMP_HEAD_RC EQUAL 0)
        message(FATAL_ERROR
            "nesrecomp pin check: failed to read HEAD of ${NESRECOMP_ROOT}. "
            "Is the directory a valid git checkout?")
    endif()

    if(NOT NESRECOMP_ACTUAL_SHA STREQUAL NESRECOMP_EXPECTED_SHA)
        message(FATAL_ERROR
            "nesrecomp pin mismatch.\n"
            "  expected: ${NESRECOMP_EXPECTED_SHA}  (from ${NESRECOMP_PIN_SOURCE})\n"
            "  actual:   ${NESRECOMP_ACTUAL_SHA}  (HEAD of ${NESRECOMP_ROOT})\n"
            "\n"
            "To align the central nesrecomp checkout, run:\n"
            "  git -C ${NESRECOMP_ROOT} checkout ${NESRECOMP_EXPECTED_SHA}\n"
            "\n"
            "Or, if you want to roll this game forward to the actual SHA, edit "
            "${CMAKE_SOURCE_DIR}/nesrecomp.pin (set sha=${NESRECOMP_ACTUAL_SHA} "
            "or clear sha to track the branch tip) and commit.")
    endif()
    message(STATUS "nesrecomp pin OK: ${NESRECOMP_EXPECTED_SHA} (${NESRECOMP_PIN_SOURCE})")
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

# ---- Nestopia Oracle integration ----
if(ENABLE_NESTOPIA_ORACLE)
    target_link_libraries(FaxanaduRecomp PRIVATE nestopia_core)
    target_compile_definitions(FaxanaduRecomp PRIVATE ENABLE_NESTOPIA_ORACLE)
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
recomp_target_launcher_ui(FaxanaduRecomp BOXART ${CMAKE_SOURCE_DIR}/boxart.tga)
if(WIN32)
    # OpenGL for the ImGui GL3 backend (previously pulled in by the RmlUi
    # launcher.cmake via OpenGL::GL).
    target_link_libraries(FaxanaduRecomp PRIVATE opengl32)
endif()

# Faxanadu saves via a password (mantra), not battery SRAM. Drive the launcher's
# SAVES panel to show/edit that password (the faxanadu.srm sidecar next to the exe
# that the runtime auto-prefill reads/writes) instead of the binary SRAM UI.
target_compile_definitions(FaxanaduRecomp PRIVATE
    NESRECOMP_GAME_PASSWORD_SAVE="faxanadu.srm"
    NESRECOMP_GAME_PASSWORD_SAVE_LABEL="Mantra")
