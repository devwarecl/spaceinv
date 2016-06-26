
#pragma once

#ifndef __gl3_subset__
#define __gl3_subset__

#include <memory>
#include "xe/DataFormat.hpp"
#include "xe/gfx/Mesh.hpp"
#include "BufferGL.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class MeshGL : public Mesh {
    public:
        MeshGL() {}
        
        MeshGL(const MeshFormat &format, std::vector<BufferPtr> buffers) {
            this->construct(format, std::move(buffers));
        }
        
        ~MeshGL();

        GLuint getId() const {
            return m_id;
        }

        virtual bool isIndexed() const override {
            return m_indexed;
        }

		virtual std::size_t getBufferCount() const override {
			return m_buffers.size();
		}

		virtual Buffer* getBuffer(const std::size_t index)  override {
			return m_buffers[index].get();
		}

		virtual const Buffer* getBuffer(const std::size_t index) const override {
			return m_buffers[index].get();
		}

		MeshFormat getFormat() const override {
			return m_format;
		}

    protected:
        void construct(const MeshFormat &format, std::vector<BufferPtr> buffers);

    private:
        GLuint m_id = 0;
        bool m_indexed = false;
        std::vector<BufferGLPtr> m_buffers;
		MeshFormat m_format;
    };

	typedef std::unique_ptr<MeshGL> MeshGLPtr;
}}}

#endif
