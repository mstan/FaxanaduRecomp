cmake_minimum_required(VERSION 3.20)
project(FaxanaduLinkTests C)
set(CMAKE_C_STANDARD 11)
if(NOT NESRECOMP_ROOT)
    message(FATAL_ERROR "Set NESRECOMP_ROOT to the game's cycle engine checkout")
endif()
add_executable(link_controller_test controller_test.c
    ../../mods/zelda2/link_controller.c
    ${NESRECOMP_ROOT}/runner/src/foreign_controller.c
    ${NESRECOMP_ROOT}/runner/cyc/cpu6502.c
    ${NESRECOMP_ROOT}/runner/cyc/cpu6502_interp.c)
target_include_directories(link_controller_test PRIVATE ../.. ${NESRECOMP_ROOT}/runner/include ${NESRECOMP_ROOT}/runner/cyc)
if(NOT MSVC)
    target_link_libraries(link_controller_test PRIVATE m)
endif()
