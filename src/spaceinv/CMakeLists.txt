
set (target spaceinv)

set (sources SpaceInvApp.cpp Player.hpp Player.cpp)

set (sources_render
	render/Mesh.hpp 
	render/TextureLoader.hpp render/TextureLoader.cpp 
	render/MeshLoader.cpp render/MeshLoader.hpp 
	render/PhongPipeline.hpp render/PhongPipeline.cpp
)

set (sources_render_gl3 
	render/gl3/GL.hpp 
	render/gl3/Buffer.hpp 
	render/gl3/Device.hpp render/gl3/Device.cpp 
	render/gl3/Material.hpp 
	render/gl3/Program.hpp render/gl3/Program.cpp 
	render/gl3/Subset.hpp
)

source_group(\\     		FILES ${sources})
source_group(\\render  		FILES ${sources_render})
source_group(\\render\\gl3  FILES ${sources_render_gl3})

add_executable(${target} ${sources} ${sources_render} ${sources_render_gl3})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glbinding bdm freeimage xe)
