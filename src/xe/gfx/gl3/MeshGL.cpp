
#include "MeshGL.hpp"

namespace xe { namespace gfx { namespace gl3  {
    static GLenum conv_type(xe::DataType type) {
        switch (type) {
            case xe::DataType::Float32: return GL_FLOAT;
            case xe::DataType::Int32:   return GL_INT;
            default: assert(false); return GL_UNSIGNED_SHORT;
        }
    }

	MeshGL::~MeshGL() {
        if (m_id) {
            glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    void MeshGL::construct(const MeshFormat &format, std::vector<BufferPtr> buffers_, BufferPtr ibuffer_) {
        buffers = std::move(buffers_);
        ibuffer = std::move(ibuffer_);
        
        glGenVertexArrays(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);

        glBindVertexArray(m_id);
        assert(glGetError() == GL_NO_ERROR);

        GLuint vertexAttrib = 0;

        for (const MeshAttrib &attrib : format.attribs) {
            if (attrib.type == xe::DataType::Unknown) {
                break;
            }

            auto buffer = buffers[attrib.bufferIndex].get();

            glBindBuffer(buffer->getTarget(), buffer->getId());
            assert(glGetError() == GL_NO_ERROR);
                
            glEnableVertexAttribArray(vertexAttrib);
            assert(glGetError() == GL_NO_ERROR);

            glVertexAttribPointer(vertexAttrib, attrib.count, conv_type(attrib.type), GL_FALSE, 0, nullptr);
            assert(glGetError() == GL_NO_ERROR);

            ++vertexAttrib;
        }

        if (ibuffer) {
            glBindBuffer(ibuffer->getTarget(), ibuffer->getId());
            glBindVertexArray(0);
            _indexed = true;

            assert(glGetError() == GL_NO_ERROR);
        }
    }
}}}
