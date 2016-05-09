
set (target spaceinv)
set (sources SpaceInvApp.cpp)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glbinding)
