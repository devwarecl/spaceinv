
set (target spaceinv)

set (sources SpaceInvApp.hpp SpaceInvApp.cpp Player.hpp Player.cpp Model.cpp Model.hpp)

set (sources_render
	render/Mesh.hpp 
	render/TextureLoader.hpp render/TextureLoader.cpp 
	render/MeshLoader.cpp render/MeshLoader.hpp 
	render/PhongPipeline.hpp render/PhongPipeline.cpp
)

set (sources_render_gl3 

)

source_group(\\     		FILES ${sources})
source_group(\\render  		FILES ${sources_render})
source_group(\\render\\gl3  FILES ${sources_render_gl3})

add_executable(${target} ${sources} ${sources_render} ${sources_render_gl3})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glbinding bdm freeimage xe)
