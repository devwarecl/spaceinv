
#pragma once

#ifndef __xe_gfx_subset__
#define __xe_gfx_subset__

#include "xe/Buffer.hpp"
#include "xe/DataFormat.hpp"
#include "xe/gfx/BufferType.hpp"

namespace xe { namespace gfx {

    struct MeshAttrib : public Attrib {
        int bufferIndex = 0;
    };

	typedef xe::DataFormat<MeshAttrib> MeshFormat;

    class Mesh {
    public:
        virtual ~Mesh() {}

        virtual std::size_t getBufferCount() const = 0;
        virtual Buffer* getBuffer(const std::size_t index) = 0;
        virtual const Buffer* getBuffer(const std::size_t index) const = 0;
    };
}}

#endif 
