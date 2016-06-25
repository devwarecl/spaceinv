#pragma once

#ifndef __gl3_texture__
#define __gl3_texture__

#include <cassert>

#include "OpenGL.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/Texture.hpp"

namespace gl3 {

    class TextureGL : public xe::gfx::Texture {
    public:
        TextureGL(unsigned int width, unsigned int height, const void *data, GLenum srcformat = GL_RGB);

        GLuint getId() const {
            return m_id;
        }

		virtual xe::gfx::TextureDesc getDesc() const override {
			return m_desc;
		}

		virtual xe::Buffer* getBuffer(xe::gfx::TextureCubeSide side = xe::gfx::TextureCubeSide::Unknown, size_t level = 0) override;

		virtual const xe::Buffer* getBuffer(xe::gfx::TextureCubeSide side = xe::gfx::TextureCubeSide::Unknown, size_t level = 0) const override;

    private:
        GLuint m_id = 0;
        
		xe::gfx::TextureDesc m_desc;
    };

    typedef std::unique_ptr<TextureGL> TexturePtr;
}

#endif 
