
#pragma once

#ifndef __gl3_material__
#define __gl3_material__

#include "GL.hpp"
#include "xe/DataFormat.hpp"

namespace gl3 {

    typedef xe::DataFormat<xe::Attrib> MaterialFormat;

    struct Material {
        bool depthTest = true;
        bool cullFace = true;
    
        const MaterialFormat &format;

        void *data = nullptr;

        explicit Material(const MaterialFormat &format_) : format(format_) {
            data = std::malloc(format.getSize());
        }

        ~Material() {
            std::free(data);
        }
    };
}

#endif
