
#pragma once

#ifndef __gl3_subset__
#define __gl3_subset__

#include <memory>
#include "xe/DataFormat.hpp"
#include "Buffer.hpp"

namespace gl3 {

    struct MeshAttrib : public xe::Attrib {
        int bufferIndex = 0;

        MeshAttrib() {}

        MeshAttrib(const std::string &name_, std::size_t count_, xe::DataType type_, int bufferIndex_) {
            name = name_;
            count = count_;
            type = type_;
            bufferIndex = bufferIndex_;
        }
    };

    typedef xe::DataFormat<MeshAttrib> MeshFormat;

    inline GLenum conv_type(xe::DataType type) {
        switch (type) {
            case xe::DataType::Float32: return GL_FLOAT;
            case xe::DataType::Int32:   return GL_INT;
            default: assert(false); return GL_UNSIGNED_SHORT;
        }
    }

    class Mesh {
    public:
        Mesh() {}
        
        Mesh(const MeshFormat &format, std::vector<BufferPtr> buffers_) {
            
            BufferPtr ibuffer_;
            
            construct(format, std::move(buffers_), std::move(ibuffer_));
        }
        
        Mesh(const MeshFormat &format, std::vector<BufferPtr> buffers_, BufferPtr ibuffer_) {
            construct(format, std::move(buffers_), std::move(ibuffer_));
        }

        ~Mesh() {
            if (id) {
                glDeleteVertexArrays(1, &id);
                id = 0;
            }

            assert(glGetError() == GL_NO_ERROR);
        }

        GLuint getId() const {
            return id;
        }

        bool indexed() const {
            return _indexed;
        }

    protected:
        void construct(const MeshFormat &format, std::vector<BufferPtr> buffers_, BufferPtr ibuffer_) {
        
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

    private:
        GLuint id = 0;
        bool _indexed = false;
        std::vector<BufferPtr> buffers;
        BufferPtr ibuffer;
    };
    
    typedef std::unique_ptr<Mesh> MeshPtr;
}

#endif
