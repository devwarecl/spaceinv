
#include "ProgramGL.hpp"

#include <iostream>

namespace gl3 {

	ShaderGL::ShaderGL(GLenum type_, const std::string &glsl) {
        type = type_;
        m_id = glCreateShader(type);

        auto source = static_cast<const GLchar *const>(glsl.c_str());
        auto size = static_cast<GLsizei>(glsl.size());
        glShaderSource (m_id, 1, &source, &size);
        glCompileShader(m_id);

        // check for errors
        GLint status;
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);

        if (status == static_cast<GLint>(GL_FALSE)) {
            const GLint logsize = 4096;
            char buffer[logsize] = {};
                
            glGetShaderInfoLog(m_id, logsize, nullptr, buffer);
                
            std::cerr << buffer << std::endl;

            throw std::runtime_error(buffer);
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    ShaderGL::~ShaderGL() {
        if (m_id) {
            glDeleteShader(m_id);
            m_id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }
}

namespace gl3 {
	ProgramGL::ProgramGL(ShaderVector shaders) {
        m_shaders = std::move(shaders);

        m_id = glCreateProgram();

        assert(glGetError() == GL_NO_ERROR);

        for (auto &shader : m_shaders) {
            assert(shader->getId());

            glAttachShader(m_id, shader->getId());
        }

        glLinkProgram(m_id);

        assert(glGetError() == GL_NO_ERROR);

        // check for errors
        GLint status;

        glGetProgramiv(m_id, GL_LINK_STATUS, &status);
        assert(glGetError() == GL_NO_ERROR);

        if (status == static_cast<GLint>(GL_FALSE)) {
            const GLint logsize = 4096;
            char buffer[logsize] = {};

            glGetProgramInfoLog(m_id, logsize, nullptr, buffer);
                
            std::cerr << buffer << std::endl;
                
            throw std::runtime_error(buffer);
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    ProgramGL::~ProgramGL() {
        if (m_id) {
            glDeleteProgram(m_id);
            m_id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    GLint ProgramGL::getLocation(const char *uniformName) const {
        assert(uniformName);

        GLint location = glGetUniformLocation(m_id, uniformName);

        if (location < 0) {
            // std::cerr << uniformName << std::endl;
        }

        // assert(location >= 0);

        return location;
    }

	void ProgramGL::getUniformLocations(UniformFormat *uniformFormat) {
		assert(uniformFormat);

		for (UniformDescriptor &desc : uniformFormat->attribs) {
			desc.location = glGetUniformLocation(m_id, desc.name.c_str());
		}

		assert(glGetError() == GL_NO_ERROR);
	}
}
