
#include "MeshGL.hpp"

namespace gl3 {
    static GLenum conv_type(xe::DataType type) {
        switch (type) {
            case xe::DataType::Float32: return GL_FLOAT;
            case xe::DataType::Int32:   return GL_INT;
            default: assert(false); return GL_UNSIGNED_SHORT;
        }
    }

	MeshGL::~MeshGL() {
        if (id) {
            glDeleteVertexArrays(1, &id);
            id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    void MeshGL::construct(const MeshFormat &format, std::vector<BufferPtr> buffers_, BufferPtr ibuffer_) {
        buffers = std::move(buffers_);
        ibuffer = std::move(ibuffer_);
        
        glGenVertexArrays(1, &id);
        assert(glGetError() == GL_NO_ERROR);

        glBindVertexArray(id);
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
}
