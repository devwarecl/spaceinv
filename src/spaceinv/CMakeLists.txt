
set (target spaceinv)

set (sources 
    Game.hpp 
    Game.cpp 
    Entity.hpp 
    Entity.cpp 
    Missile.hpp 
    Missile.cpp
    Config.hpp
    Updatable.hpp
    Scenario.hpp 
    Scenario.cpp
    Floor.hpp 
    Floor.cpp
)

set (sources_render
    render/Model.hpp            
    render/Model.cpp
    render/TextureLoader.hpp    
    render/TextureLoader.cpp 
    render/BdmModelLoader.cpp   
    render/BdmModelLoader.hpp 
    render/BdmModel.hpp         
    render/BdmModel.cpp 
    render/BdmModelPart.hpp     
    render/BdmModelPart.cpp 
    render/PhongPipeline.hpp    
    render/PhongPipeline.cpp
    render/PhongPipeline2.hpp   
    render/PhongPipeline2.cpp
    render/PhongMaterial.hpp    
    render/PhongMaterial.cpp 
    render/LookAtCamera.hpp
)

source_group(\\         FILES ${sources})
source_group(\\render   FILES ${sources_render})

add_executable(${target} ${sources} ${sources_render})

target_link_libraries(${target} ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} ${OPENAL_LIBRARY} glbinding bdm freeimage xe)
