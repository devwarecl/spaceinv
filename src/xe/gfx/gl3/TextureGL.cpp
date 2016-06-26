
#include "TextureGL.hpp"
#include "Util.hpp"

namespace xe { namespace gfx { namespace gl3  {

	TextureGL::TextureGL(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData) {
		GLenum target = convertTarget(desc.type);
		GLint iformat = (GLint)convertFormat(desc.format);
		
		GLenum sformat = convertFormat(sourceFormat);
		GLenum type = convertDataType(sourceType);

        ::glGenTextures(1, &m_id);
        ::glBindTexture(target, m_id);

		switch (target) {
		case GL_TEXTURE_1D:
			::glTexImage1D(target, 0, iformat, desc.width, 0, sformat, type, sourceData);
			break;

		case GL_TEXTURE_2D:
			::glTexImage2D(target, 0, iformat, desc.width, desc.height, 0, sformat, type, sourceData);
			break;

		case GL_TEXTURE_3D:
			::glTexImage3D(target, 0, iformat, desc.width, desc.height, desc.depth, 0, sformat, type, sourceData);
			break;

		case GL_TEXTURE_CUBE_MAP: 
			for (int i=0; i<6; i++) {
				::glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, iformat, desc.width, desc.height, 0, sformat, type, sourceData);
			}
			break;
		}

        ::glTexParameteri(target, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_LINEAR));
        ::glTexParameteri(target, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_LINEAR));

        ::glBindTexture(target, 0);

        assert(glGetError() == GL_NO_ERROR);

		m_target = target;
		m_desc = desc;
    }

	xe::Buffer* TextureGL::getBuffer(xe::gfx::TextureCubeSide side, size_t level) {
		return nullptr;
	}

	const xe::Buffer* TextureGL::getBuffer(xe::gfx::TextureCubeSide side, size_t level) const {
		return nullptr;
	}
}}}
