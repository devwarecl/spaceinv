
#pragma once

#ifndef __gl3_subset__
#define __gl3_subset__

#include <memory>
#include "xe/DataFormat.hpp"
#include "BufferGL.hpp"

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

    class MeshGL {
    public:
        MeshGL() {}
        
        MeshGL(const MeshFormat &format, std::vector<BufferPtr> buffers_) {
            
            BufferPtr ibuffer_;
            
            construct(format, std::move(buffers_), std::move(ibuffer_));
        }
        
        MeshGL(const MeshFormat &format, std::vector<BufferPtr> buffers_, BufferPtr ibuffer_) {
            construct(format, std::move(buffers_), std::move(ibuffer_));
        }

        ~MeshGL();

        GLuint getId() const {
            return id;
        }

        bool indexed() const {
            return _indexed;
        }

    protected:
        void construct(const MeshFormat &format, std::vector<BufferPtr> buffers_, BufferPtr ibuffer_);

    private:
        GLuint id = 0;
        bool _indexed = false;
        std::vector<BufferPtr> buffers;
        BufferPtr ibuffer;
    };
    
    typedef std::unique_ptr<MeshGL> MeshPtr;
}

#endif
