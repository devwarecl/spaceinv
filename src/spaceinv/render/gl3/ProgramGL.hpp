
#pragma once

#ifndef __gl3_program__
#define __gl3_program__

#include <memory>
#include <cassert>
#include "GL.hpp"

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
            return id;
        }

    private:
        GLenum type;
        GLuint id = 0;
    };
    
    typedef std::unique_ptr<ShaderGL> ShaderPtr;
    typedef std::vector<ShaderPtr> ShaderVector;
    
    class ProgramGL {
    public:
        ProgramGL() {}

        explicit ProgramGL(ShaderVector shaders_);

        GLuint getId() const {
            return id;
        }

        ~ProgramGL();

        GLint getLocation(const char *uniformName) const;

    private:
        GLuint id = 0;
        ShaderVector shaders;
    };
    
    typedef std::unique_ptr<ProgramGL> ProgramPtr;
}

#endif
