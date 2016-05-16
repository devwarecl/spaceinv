
#pragma once

#ifndef __gl3_program__
#define __gl3_program__

#include <cassert>
#include "GL.hpp"

namespace gl3 {

    class Shader {
    public:
        Shader() {}

        Shader(GLenum type_, const std::string &glsl) {
            type = type_;
            id = glCreateShader(type);

            auto source = static_cast<const GLchar *const>(glsl.c_str());
            auto size = static_cast<GLsizei>(glsl.size());
            glShaderSource (id, 1, &source, &size);
            glCompileShader(id);

            // check for errors
            GLint status;
            glGetShaderiv(id, GL_COMPILE_STATUS, &status);

            if (status == static_cast<GLint>(GL_FALSE)) {
                char buffer[2048] = {};
                glGetShaderInfoLog(id, 2048, nullptr, buffer);

                throw std::runtime_error(buffer);
            }

            assert(glGetError() == GL_NO_ERROR);
        }

        ~Shader() {
            if (id) {
                glDeleteShader(id);
                id = 0;
            }

            assert(glGetError() == GL_NO_ERROR);
        }

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

    class Program {
    public:
        typedef std::vector<Shader> ShaderVector;

        Program() {}

        Program(ShaderVector shaders_) {
            shaders = std::move(shaders_);

            id = glCreateProgram();

            assert(glGetError() == GL_NO_ERROR);

            for (const Shader &shader : shaders) {
                assert(shader.getId());

                glAttachShader(id, shader.getId());
            }

            glLinkProgram(id);

            assert(glGetError() == GL_NO_ERROR);

            // check for errors
            GLint status;
            glGetShaderiv(id, GL_LINK_STATUS, &status);

            if (status == static_cast<GLint>(GL_FALSE)) {
                char buffer[2048] = {};
                glGetShaderInfoLog(id, 2048, nullptr, buffer);

                throw std::runtime_error(buffer);
            }

            assert(glGetError() == GL_NO_ERROR);
        }

        GLuint getId() const {
            return id;
        }

        ~Program() {
            if (id) {
                glDeleteProgram(id);
                id = 0;
            }

            assert(glGetError() == GL_NO_ERROR);
        }

        GLint getLocation(const char *uniformName) const {
            assert(uniformName);

            GLint location = glGetUniformLocation(id, uniformName);

            assert(location >= 0);

            return location;
        }

    private:
        GLuint id = 0;
        std::vector<Shader> shaders;
    };
}

#endif
