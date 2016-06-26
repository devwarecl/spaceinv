
#include "MeshGL.hpp"
#include "Util.hpp"

namespace xe { namespace gfx { namespace gl3  {
    
	MeshGL::~MeshGL() {
        if (m_id) {
            glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }

        assert(glGetError() == GL_NO_ERROR);
    }

    void MeshGL::construct(const MeshFormat &format, std::vector<BufferPtr> buffers) {
		//!TODO: Implement proper construction with only one buffer for all attributes
		m_format = format;

		for (BufferPtr &buffer : buffers) {
			m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
		}

        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        assert(glGetError() == GL_NO_ERROR);

        GLuint vertexAttrib = 0;

        for (const MeshAttrib &attrib : format.attribs) {
            if (attrib.type == xe::DataType::Unknown) {
                break;
            }

			if (attrib.bufferType == BufferType::Index) {
				m_indexed = true;
			}

            auto buffer = m_buffers[attrib.bufferIndex].get();

            glBindBuffer(buffer->getTarget(), buffer->getId());
            glEnableVertexAttribArray(vertexAttrib);
            glVertexAttribPointer(vertexAttrib, attrib.count, convertDataType(attrib.type), GL_FALSE, 0, nullptr);
            assert(glGetError() == GL_NO_ERROR);

            ++vertexAttrib;
        }		
    }
}}}
