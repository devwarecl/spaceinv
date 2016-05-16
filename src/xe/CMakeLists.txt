
set (target xe)

set (sources Buffer.hpp DataFormat.hpp DataType.hpp Traits.hpp Vector.hpp Matrix.hpp Quaternion.hpp)

set (sources_gfx 
    gfx/Device.hpp gfx/Device.cpp 
    gfx/BufferType.hpp
    gfx/Program.hpp
    gfx/ShaderType.hpp
    gfx/Subset.hpp
)

source_group(\\ 	FILES ${sources})
source_group(\\gfx 	FILES ${sources_gfx})

add_library(${target} ${sources} ${sources_gfx})
