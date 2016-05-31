
#pragma once

#ifndef __gl3_program__
#define __gl3_program__

#include <memory>
#include <cassert>
#include "GL.hpp"

namespace gl3 {

    class Shader {
    public:
        Shader() {}

        Shader(GLenum type_, const std::string &glsl) ;

        ~Shader();

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
    
    typedef std::unique_ptr<Shader> ShaderPtr;
    typedef std::vector<ShaderPtr> ShaderVector;
    
    class Program {
    public:
        Program() {}

        explicit Program(ShaderVector shaders_);

        GLuint getId() const {
            return id;
        }

        ~Program();

        GLint getLocation(const char *uniformName) const;

    private:
        GLuint id = 0;
        ShaderVector shaders;
    };
    
    typedef std::unique_ptr<Program> ProgramPtr;
}

#endif
