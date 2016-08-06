
#include "xe/gfx/Material.hpp"

#ifndef __modelmaterial__
#define __modelmaterial__

struct ModelMaterial : public xe::gfx::Material {
    struct Attributes {
        xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        xe::Vector4f diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
        xe::Vector4f emissive = {0.0f, 0.0f, 0.0f, 1.0f};
        float shininess = 0.0f;
        int tex_diffuse = 0;
    };

    Attributes attribs;

    explicit ModelMaterial(xe::gfx::UniformFormat *format);

    virtual const void* getUniformPointer() const {
        return &attribs;
    }
};

#endif
