
cmake_minimum_required(VERSION 3.2)

project(spaceinv)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)

set (CMAKE_CXX_STANDARD 14)
set (target spaceinv)
set (sources SpaceInvApp.cpp)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glbinding)
