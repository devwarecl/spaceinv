
#pragma once 

#ifndef __xe_gfx_program__
#define __xe_gfx_program__

#include "xe/gfx/ShaderType.hpp"

namespace xe { namespace gfx {

    class Shader {
    public:
        virtual ~Shader() {}

        virtual ShaderType getShaderType() const = 0;

    };

    class Program {
    public:
        virtual ~Program() {}

    };
}}

#endif 
