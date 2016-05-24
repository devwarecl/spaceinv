#pragma once

#ifndef __gl3_texture__
#define __gl3_texture__



namespace gl3 {

    class Texture {
    public:
        Texture(unsigned int width, unsigned int height, const void *data, GLenum srcformat = GL_RGB) {
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

            m_width = width;
            m_height = height;
        }

        unsigned int getWidth() const {
            return m_width;
        }

        unsigned int getHeight() const {
            return m_height;
        }

        xe::Vector2i getSize() const {
            return xe::Vector2i(m_width, m_height);
        }

        GLuint getId() const {
            return m_id;
        }

    private:
        GLuint m_id = 0;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
    };

    typedef std::unique_ptr<Texture> TexturePtr;
}

#endif 
