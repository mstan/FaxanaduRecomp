cmake_minimum_required(VERSION 3.20)
project(FaxanaduRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)
include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

# ---- FCEUX Oracle (optional) ----
option(ENABLE_FCEUX_ORACLE "Build with FCEUX emulator oracle for verify mode" OFF)

set(FCEUX_SOURCES "")
if(ENABLE_FCEUX_ORACLE)
    include(${CMAKE_SOURCE_DIR}/fceux-core/CMakeLists_core.cmake)
endif()

# ---- Main executable ----
add_executable(FaxanaduRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    extras.c
    debug_server.c
    recomp_stack.c
    nes_snapshot.c
    verify_mode.c
    watchdog.c
    generated/faxanadu_full.c
    generated/faxanadu_dispatch.c
)

target_compile_definitions(FaxanaduRecomp PRIVATE RECOMP_STACK_TRACKING WATCHDOG_ENABLED)

target_include_directories(FaxanaduRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(FaxanaduRecomp PRIVATE ${SDL2_LIBRARIES})

if(WIN32)
    target_link_libraries(FaxanaduRecomp PRIVATE ws2_32)
endif()

# ---- FCEUX Oracle integration ----
if(ENABLE_FCEUX_ORACLE)
    # Add bridge (C++ source) — no stubs needed, real Win32 driver is included
    target_sources(FaxanaduRecomp PRIVATE
        fceux_bridge.cpp
    )
    target_link_libraries(FaxanaduRecomp PRIVATE fceux_core)
    target_compile_definitions(FaxanaduRecomp PRIVATE ENABLE_FCEUX_ORACLE __WIN_DRIVER__)
    target_include_directories(FaxanaduRecomp PRIVATE
        ${CMAKE_SOURCE_DIR}/fceux-core/src
        ${CMAKE_SOURCE_DIR}/fceux-core/src/drivers/win/zlib
        ${CMAKE_SOURCE_DIR}/fceux-core/src/drivers/win/directx
        ${CMAKE_SOURCE_DIR}/fceux-core/src/lua/src
    )
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
