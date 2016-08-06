
#include "xe/gfx/gl3/ProgramGL.hpp"
#include "xe/gfx/gl3/Util.hpp"

#include <iostream>

namespace xe { namespace gfx { namespace gl3  {
    ProgramGL::ProgramGL(ShaderGLVector shaders) {
        m_shaders = std::move(shaders);

        m_id = glCreateProgram();

        XE_GL_CHECK_ERROR();

        for (auto &shader : m_shaders) {
            assert(shader->getId());

            glAttachShader(m_id, shader->getId());
        }

        glLinkProgram(m_id);

        XE_GL_CHECK_ERROR();

        // check for errors
        GLint status;

        glGetProgramiv(m_id, GL_LINK_STATUS, &status);
        XE_GL_CHECK_ERROR();

        if (status == static_cast<GLint>(GL_FALSE)) {
            const GLint logsize = 4096;
            char buffer[logsize] = {};

            glGetProgramInfoLog(m_id, logsize, nullptr, buffer);
                
            std::cerr << buffer << std::endl;
                
            throw std::runtime_error(buffer);
        }

        XE_GL_CHECK_ERROR();
    }

    ProgramGL::~ProgramGL() {
        if (m_id) {
            glDeleteProgram(m_id);
            m_id = 0;
        }

        XE_GL_CHECK_ERROR();
    }

    int ProgramGL::getUniform(const std::string &uniformName) const {
        assert(m_id);

        return glGetUniformLocation(m_id, uniformName.c_str());
    }

    int ProgramGL::getAttrib(const std::string &attribName) const {
        assert(m_id);

        return glGetAttribLocation(m_id, attribName.c_str());
    }
}}}
