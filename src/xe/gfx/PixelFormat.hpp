
#ifndef __EXENG_GRAPHICS_PIXELFORMAT_HPP__
#define __EXENG_GRAPHICS_PIXELFORMAT_HPP__

#include <cstdint>

namespace xe { namespace gfx {
    
    /** 
     * @brief The image pixel format
     */
    enum class PixelFormat {
        Unknown,
        R5G5B5X1,
        R5G5B5A1,
        R5G6B5,
        R8G8B8,
        R8G8B8A8,
        B8G8R8,
        B8G8R8A8
    };

    std::size_t size(PixelFormat format);
}}

#endif
