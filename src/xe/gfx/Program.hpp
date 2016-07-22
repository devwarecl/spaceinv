
#pragma once 

#ifndef __xe_gfx_program__
#define __xe_gfx_program__

#include <memory>
#include <string>
#include <list>

#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/ShaderType.hpp"

namespace xe { namespace gfx {
    struct ShaderSource {
        xe::gfx::ShaderType type;
        std::string source;
    };

    class Program {
    public:
        virtual ~Program() {}

        virtual int getLocation(const std::string &name) const = 0;

        virtual void fillUniformLocations(UniformFormat *uniformFormat) const = 0;
    };

    typedef std::unique_ptr<Program> ProgramPtr;
}}

#endif 
