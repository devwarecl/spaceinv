
set (target spaceinv)

set (sources 
    SpaceInvApp.hpp SpaceInvApp.cpp 
    Entity.hpp Entity.cpp 
    Model.cpp Model.hpp 
    ModelPart.hpp 
    Missile.hpp Missile.cpp
    Config.hpp
    Updatable.hpp
    Scenario.hpp Scenario.cpp
	Floor.hpp Floor.cpp
	ModelMaterial.hpp ModelMaterial.cpp 
)

set (sources_render
    render/TextureLoader.hpp render/TextureLoader.cpp 
    render/ModelLoader.cpp render/ModelLoader.hpp 
    render/PhongPipeline.hpp render/PhongPipeline.cpp
)

source_group(\\         FILES ${sources})
source_group(\\render   FILES ${sources_render})

add_executable(${target} ${sources} ${sources_render} ${sources_render_gl3})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set (target_libs stdc++ m)
else ()
    set (target_libs )
endif ()

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} ${OPENAL_LIBRARY} ${target_libs} glbinding bdm freeimage xe)
