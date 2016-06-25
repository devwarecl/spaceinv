
#pragma once

#ifndef __gl3_program__
#define __gl3_program__

#include <memory>
#include <cassert>
#include "OpenGL.hpp"

#include "xe/gfx/UniformFormat.hpp"

namespace gl3 {

    class ShaderGL {
    public:
        ShaderGL() {}

        ShaderGL(GLenum type_, const std::string &glsl) ;

        ~ShaderGL();

        GLenum getType() const {
            return type;
        }

        GLuint getId() const {
            return m_id;
        }

    private:
        GLenum type;
        GLuint m_id = 0;
    };
    
    typedef std::unique_ptr<ShaderGL> ShaderPtr;
    typedef std::vector<ShaderPtr> ShaderVector;
    
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
}

#endif
