cmake_minimum_required(VERSION 3.20)
project(FaxanaduWorldPortableCompile C)
set(NESRECOMP_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../nesrecomp" CACHE PATH "Cycle engine checkout")
add_library(fax_world_no_sdl OBJECT ../../fax_world.c)
set_property(TARGET fax_world_no_sdl PROPERTY C_STANDARD 11)
target_include_directories(fax_world_no_sdl PRIVATE
    "${NESRECOMP_ROOT}/runner/cyc" "${NESRECOMP_ROOT}/runner/include")
