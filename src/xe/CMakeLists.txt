
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
)

set (sources_gfx 
    gfx/Device.hpp gfx/Device.cpp 
    gfx/BufferType.hpp
    gfx/Program.hpp
    gfx/ShaderType.hpp
    gfx/Mesh.hpp
	gfx/Texture.hpp

	gfx/Image.hpp
	
	gfx/PixelFormat.hpp
	gfx/PixelFormat.cpp
)

set (sources_sg    
	sg/Renderable.cpp
	sg/Pipeline.cpp
    sg/SceneNode.cpp 
    sg/Scene.cpp
	sg/SceneNodeAnimator.cpp
	sg/SceneLoader.cpp
	sg/SceneManager.cpp
	sg/SceneRenderer.cpp
	sg/SceneRendererImpl.cpp
	sg/SceneLoader.cpp
    sg/Camera.cpp 
    sg/Light.cpp
    sg/Geometry.cpp
	sg/AssetsLibrary.cpp
	sg/GeometryLibrary.cpp

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
	sg/SceneRenderer.hpp
    sg/SceneRendererImpl.hpp
	sg/SceneLoader.hpp
	sg/SceneManager.hpp
	sg/SceneNodeAnimator.hpp
	sg/AssetsLibrary.hpp
	sg/GeometryLibrary.hpp
)

source_group(\\ 	FILES ${sources})
source_group(\\gfx 	FILES ${sources_gfx})
source_group(\\sg 	FILES ${sources_sg})

add_library(${target} ${sources} ${sources_gfx} ${sources_sg})

target_link_libraries(${target} ${Boost_LIBRARIES})
