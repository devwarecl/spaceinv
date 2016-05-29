
set (target spaceinv)
set (sources SpaceInvApp.cpp Mesh.hpp TextureLoader.hpp TextureLoader.cpp MeshLoader.cpp MeshLoader.hpp)
set (sources_gl3 gl3/GL.hpp gl3/Buffer.hpp gl3/Device.hpp gl3/Material.hpp gl3/Program.hpp gl3/Subset.hpp)

source_group(\\     FILES ${sources})
source_group(\\gl3  FILES ${sources_gl3})

add_executable(${target} ${sources} ${sources_gl3})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glbinding bdm FreeImage)
