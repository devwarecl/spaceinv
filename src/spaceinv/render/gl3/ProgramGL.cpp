
#include "ProgramGL.hpp"

#include <iostream>

namespace gl3 {

	ShaderGL::ShaderGL(GLenum type_, const std::string &glsl) {
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
            const GLint logsize = 4096;
            char buffer[logsize] = {};
                
            glGetShaderInfoLog(id, logsize, nullptr, buffer);
                
            std::cerr << buffer << std::endl;

            throw std::runtime_error(buffer);
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    ShaderGL::~ShaderGL() {
        if (id) {
            glDeleteShader(id);
            id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }
}

namespace gl3 {
	ProgramGL::ProgramGL(ShaderVector shaders_) {
        shaders = std::move(shaders_);

        id = glCreateProgram();

        assert(glGetError() == GL_NO_ERROR);

        for (auto &shader : shaders) {
            assert(shader->getId());

            glAttachShader(id, shader->getId());
        }

        glLinkProgram(id);

        assert(glGetError() == GL_NO_ERROR);

        // check for errors
        GLint status;

        glGetProgramiv(id, GL_LINK_STATUS, &status);
        assert(glGetError() == GL_NO_ERROR);

        if (status == static_cast<GLint>(GL_FALSE)) {
            const GLint logsize = 4096;
            char buffer[logsize] = {};

            glGetProgramInfoLog(id, logsize, nullptr, buffer);
                
            std::cerr << buffer << std::endl;
                
            throw std::runtime_error(buffer);
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    ProgramGL::~ProgramGL() {
        if (id) {
            glDeleteProgram(id);
            id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    GLint ProgramGL::getLocation(const char *uniformName) const {
        assert(uniformName);

        GLint location = glGetUniformLocation(id, uniformName);

        if (location < 0) {
            // std::cerr << uniformName << std::endl;
        }

        // assert(location >= 0);

        return location;
    }
}