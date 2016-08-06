
#pragma once

#ifndef __gl3_program__
#define __gl3_program__

#include <memory>
#include <cassert>
#include "OpenGL.hpp"

#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/Program.hpp"
#include "xe/gfx/gl3/ShaderGL.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class ProgramGL : public Program {
    public:
        ProgramGL() {}

        explicit ProgramGL(ShaderGLVector shaders);

        GLuint getId() const {
            return m_id;
        }

        virtual ~ProgramGL();

        virtual int getUniform(const std::string &uniformName) const override;

        virtual int getAttrib(const std::string &attribName) const override;

    private:
        GLuint m_id = 0;
        ShaderGLVector m_shaders;
    };
    
    typedef std::unique_ptr<ProgramGL> ProgramGLPtr;
}}}

#endif
