
#pragma once

#ifndef __xe_gfx_subset__
#define __xe_gfx_subset__

#include "xe/Buffer.hpp"
#include "xe/DataFormat.hpp"
#include "xe/gfx/BufferType.hpp"

namespace xe { namespace gfx {

    struct MeshAttrib : public Attrib {
        int bufferIndex = 0;
		BufferType bufferType = BufferType::Unknown;

        MeshAttrib() {}

        MeshAttrib(const std::string &name_, const std::size_t dim_, const DataType type_, const int bufferIndex_, const BufferType bufferType_) {
            name = name_;
            dim = dim_;
            type = type_;
            bufferIndex = bufferIndex_;
			bufferType = bufferType_;
        }
    };

	typedef xe::DataFormat<MeshAttrib> MeshFormat;

    class Mesh {
    public:
        virtual ~Mesh() {}

		virtual MeshFormat getFormat() const = 0;

        virtual std::size_t getBufferCount() const = 0;
        virtual Buffer* getBuffer(const std::size_t index) = 0;
        virtual const Buffer* getBuffer(const std::size_t index) const = 0;

		virtual bool isIndexed() const;
    };

    typedef std::unique_ptr<Mesh> MeshPtr;
}}

#endif 
