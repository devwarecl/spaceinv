
#include "BufferGL.hpp"

namespace gl3 {
	BufferGL::~BufferGL() {
        if (m_id) {
            glDeleteBuffers(1, &m_id);
            m_id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    void BufferGL::write(const void *source, const int size, const int offset, const int source_offset) {
        glBindBuffer(m_target, m_id);

		if (size) {
			glBufferSubData(m_target, 0, size, source);
		} else {
			glBufferSubData(m_target, 0, m_size, source);
		}

        glBindBuffer(m_target, 0);

        assert(glGetError() == GL_NO_ERROR);
    }

    void BufferGL::read(void* destination, const int size, const int offset, const int destination_offset) const {
        glBindBuffer(m_target, m_id);

		if (size) {
			glGetBufferSubData(m_target, 0, size, destination);
		} else {
			glGetBufferSubData(m_target, 0, m_size, destination);
		}

        glBindBuffer(m_target, 0);

        assert(glGetError() == GL_NO_ERROR);
    }

    void BufferGL::construct(GLenum target_, GLenum usage, std::size_t size_, const void *data) {
        m_size = size_;
        m_target = target_;

        glGenBuffers(1, &m_id);
        glBindBuffer(m_target, m_id);
        glBufferData(m_target, m_size, nullptr, usage);
        glBindBuffer(m_target, 0);

        assert(glGetError() == GL_NO_ERROR);

        if (data) {
            this->write(data);
        }
    }
}