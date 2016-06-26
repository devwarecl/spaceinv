
#pragma once

#include <vector>
#include <memory>
#include "xe/gfx/gl3/OpenGL.hpp"

namespace xe { namespace gfx { namespace gl3  {
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
    
    typedef std::unique_ptr<ShaderGL> ShaderGLPtr;
    typedef std::vector<ShaderGLPtr> ShaderGLVector;
    
}}}
