
#pragma once

#ifndef __gl3_program__
#define __gl3_program__

#include <memory>
#include <cassert>
#include "OpenGL.hpp"

#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/gl3/ShaderGL.hpp"

namespace xe { namespace gfx { namespace gl3  {
    class ProgramGL {
    public:
        ProgramGL() {}

        explicit ProgramGL(ShaderVector shaders);

        GLuint getId() const {
            return m_id;
        }

        ~ProgramGL();

        GLint getLocation(const char *uniformName) const;

		void getUniformLocations(UniformFormat *uniformFormat);

    private:
        GLuint m_id = 0;
        ShaderVector m_shaders;
    };
    
    typedef std::unique_ptr<ProgramGL> ProgramPtr;
}}}

#endif
