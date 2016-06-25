
#include "ShaderGL.hpp"

#include <cassert>
#include <iostream>

namespace xe { namespace gfx { namespace gl3  {

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
}}}
