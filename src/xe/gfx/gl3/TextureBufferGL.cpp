
#include "TextureGL.hpp"
#include "TextureBufferGL.hpp"

namespace xe { namespace gfx { namespace gl3 {

	std::size_t TextureBufferGL::getSize() const {
		xe::gfx::TextureDesc desc = m_texture->getDesc();

		std::size_t size = desc.width;

		if (desc.height != 0) {
			size *= desc.height;
		}

		if (desc.depth != 0) {
			size *= desc.depth;
		}

		switch (desc.format) {
		case xe::gfx::PixelFormat::R5G5B5A1:
		case xe::gfx::PixelFormat::R5G5B5X1:
		case xe::gfx::PixelFormat::R5G6B5:
			size *= 2;

		case xe::gfx::PixelFormat::R8G8B8:
			size *= 3;

		case xe::gfx::PixelFormat::R8G8B8A8:
			size *= 4;
            
        default: assert(false);
            
		}

		return size;
	}

	void TextureBufferGL::read(void* destination, const int size, const int offset, const int destination_offset) const {
		assert(size == 0);
		assert(offset == 0);
	}

	void TextureBufferGL::write(const void *source, const int size, const int offset, const int source_offset) {
		assert(source);
		assert(size == 0);
		assert(offset == 0);

		xe::gfx::TextureDesc desc = m_texture->getDesc();

		switch (desc.type) {
		case xe::gfx::TextureType::Tex1D:
			glTexSubImage1D(GL_TEXTURE_1D, 0, 0, desc.width, GL_RG, GL_UNSIGNED_BYTE, (const char*)source + source_offset);
            
        default: assert(false);
		}
	}
}}}
