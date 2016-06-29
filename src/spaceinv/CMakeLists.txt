
set (target spaceinv)

set (sources SpaceInvApp.hpp SpaceInvApp.cpp Entity.hpp Entity.cpp Model.cpp Model.hpp ModelPart.hpp Scenario.hpp Scenario.cpp)

set (sources_render
	render/TextureLoader.hpp render/TextureLoader.cpp 
	render/ModelLoader.cpp render/ModelLoader.hpp 
	render/PhongPipeline.hpp render/PhongPipeline.cpp
)

set (sources_render_gl3 

)

source_group(\\     		FILES ${sources})
source_group(\\render  		FILES ${sources_render})
source_group(\\render\\gl3  FILES ${sources_render_gl3})

add_executable(${target} ${sources} ${sources_render} ${sources_render_gl3})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} glbinding bdm freeimage xe)
