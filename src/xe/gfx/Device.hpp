
#pragma once

#ifndef __xe_gfx_device_hpp__
#define __xe_gfx_device_hpp__

#include "xe/Buffer.hpp"

namespace xe { namespace gfx {

    enum class BufferType {
        Unknown,
        Vertex, 
        Index
    };

    class Device {
    public:
        virtual ~Device() {}

        virtual Buffer::Ptr createBuffer(BufferType type, std::size_t size, void* data=nullptr) = 0;
    };
}}

#endif
