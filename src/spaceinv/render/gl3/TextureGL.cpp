
#include "TextureGL.hpp"

namespace gl3 {
	TextureGL::TextureGL(unsigned int width, unsigned int height, const void *data, GLenum srcformat) {
        assert(width);
        assert(height);
        assert(data);

        ::glGenTextures(1, &m_id);
        ::glBindTexture(GL_TEXTURE_2D, m_id);
        ::glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(GL_RGB), width, height, 0, srcformat, GL_UNSIGNED_BYTE, data);
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_LINEAR));
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_LINEAR));

        ::glBindTexture(GL_TEXTURE_2D, 0);

        assert(glGetError() == GL_NO_ERROR);

		m_desc.width = width;
		m_desc.height = height;
    }

	xe::Buffer* TextureGL::getBuffer(xe::gfx::TextureCubeSide side, size_t level) {
		return nullptr;
	}

	const xe::Buffer* TextureGL::getBuffer(xe::gfx::TextureCubeSide side, size_t level) const {
		return nullptr;
	}
}
