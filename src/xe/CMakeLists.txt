
set (target xe)

set (sources 
    Buffer.hpp 
    Common.hpp 
    DataFormat.hpp 
    DataType.hpp 
    Traits.hpp 
    Vector.hpp 
    Matrix.hpp 
    Quaternion.hpp 
    Boundary.hpp
    FileLocator.hpp FileLocator.cpp
    FileUtil.hpp FileUtil.cpp
)

set (sources_input
    input/EventImpl.hpp 
    input/Event.hpp 
    input/EventHandler.hpp 
    input/InputDevice.hpp 
    input/InputManager.hpp 
    input/Keyboard.hpp 
    input/Mouse.hpp 
    input/InputManagerImpl.hpp  input/InputManagerImpl.cpp 
    input/KeyboardStatus.hpp    input/KeyboardStatus.cpp 
    input/KeyCode.hpp 
    input/KeyStatus.hpp 
    input/KeyStroke.hpp 
)

set (sources_gfx 
    gfx/Device.hpp gfx/Device.cpp 
    gfx/BufferType.hpp
    gfx/Program.hpp gfx/Program.cpp
    gfx/ShaderType.hpp
    gfx/Mesh.hpp gfx/Mesh.cpp
    gfx/Texture.hpp gfx/Texture.cpp
    gfx/Image.hpp
    gfx/PixelFormat.hpp gfx/PixelFormat.cpp
    gfx/UniformFormat.hpp
	gfx/Material.hpp
)

set (sources_gfx_gl3
    gfx/gl3/OpenGL.hpp 
    gfx/gl3/BufferGL.hpp        gfx/gl3/BufferGL.cpp
    gfx/gl3/DeviceGL.hpp        gfx/gl3/DeviceGL.cpp 
    gfx/gl3/TextureGL.hpp       gfx/gl3/TextureGL.cpp 
    gfx/gl3/TextureBufferGL.hpp gfx/gl3/TextureBufferGL.cpp 
    gfx/gl3/MaterialGL.hpp 
    gfx/gl3/ProgramGL.hpp       gfx/gl3/ProgramGL.cpp 
    gfx/gl3/ShaderGL.hpp        gfx/gl3/ShaderGL.cpp 
    gfx/gl3/MeshGL.hpp          gfx/gl3/MeshGL.cpp

    gfx/gl3/InputManagerGLFW.hpp    gfx/gl3/InputManagerGLFW.cpp
)


set (sources_sfx
    sfx/Source.hpp sfx/Source.cpp 
    sfx/Device.hpp sfx/Device.cpp 
)

set (sources_sfx_al
    sfx/al/SourceAL.hpp sfx/al/SourceAL.cpp 
    sfx/al/BufferAL.hpp sfx/al/BufferAL.cpp 
)

set (sources_sg    
    sg/Renderable.cpp
    sg/Pipeline.cpp
    sg/SceneNode.cpp 
    sg/Scene.cpp
    sg/SceneNodeAnimator.cpp
    sg/SceneLoader.cpp
    sg/SceneManager.cpp
    sg/SceneManagerImpl.cpp
    sg/SceneLoader.cpp
    sg/Camera.cpp 
    sg/Light.cpp
    sg/Geometry.cpp
    sg/AssetsLibrary.cpp
    sg/GeometryLibrary.cpp
    sg/Renderer.cpp 
    sg/Pipeline2.cpp 

    sg/Forward.hpp 
    sg/Renderable.hpp
    sg/Pipeline.hpp
    sg/SceneNode.hpp      
    sg/Scene.hpp          
    sg/Camera.hpp         
    sg/Light.hpp          
    sg/Geometry.hpp       
    sg/TSolidGeometry.hpp 
    sg/Segment.hpp 
    sg/Box.hpp            
    sg/Ray.hpp            
    sg/Plane.hpp          
    sg/Intersect.hpp      
    sg/IntersectInfo.hpp  
    sg/Sphere.hpp
    sg/Triangle.hpp
    sg/SceneLoader.hpp
    sg/SceneManager.hpp
    sg/SceneManagerImpl.hpp
    sg/SceneNodeAnimator.hpp
    sg/AssetsLibrary.hpp
    sg/GeometryLibrary.hpp
    sg/Renderer.hpp 
    sg/Pipeline2.hpp 
)

source_group(\\         FILES ${sources})
source_group(\\gfx      FILES ${sources_gfx})
source_group(\\gfx\\gl3 FILES ${sources_gfx_gl3})
source_group(\\sfx      FILES ${sources_sfx})
source_group(\\sfx\\al  FILES ${sources_sfx_al})
source_group(\\sg       FILES ${sources_sg})
source_group(\\input    FILES ${sources_input})

add_library(${target} ${sources} ${sources_gfx} ${sources_gfx_gl3} ${sources_sfx} ${sources_sfx_al}  ${sources_sg} ${sources_input})

target_link_libraries(${target} ${Boost_LIBRARIES})
