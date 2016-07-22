
/**
 * @file Image.hpp
 * @brief Image abstract class declaration
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __EXENG_GRAPHICS_IMAGE_HPP__
#define __EXENG_GRAPHICS_IMAGE_HPP__

#include <memory>
#include "xe/Buffer.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/PixelFormat.hpp"

namespace xe { namespace gfx {

    enum class ImageType {
        Unknown,
        Img1D,
        Img2D,
        Img3D
    };
    
    struct ImageDesc {
        ImageType type = ImageType::Unknown;
        PixelFormat format = PixelFormat::Unknown;
        size_t width = 0;
        size_t height = 0;
        size_t depth = 0;
    };

    class Image {
    public:
        virtual ~Image() {}

        virtual ImageDesc getDesc() const = 0;

        virtual void* getPointer() = 0;
        virtual const void* getPointer() const = 0;
    };

    typedef std::unique_ptr<Image> ImagePtr;
}}

#endif 
