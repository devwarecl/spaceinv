
cmake_minimum_required(VERSION 3.1)

project(spaceinv)

set (target spaceinv)
set (sources SpaceInvApp.cpp)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})
