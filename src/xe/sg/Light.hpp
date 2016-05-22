
#pragma once

#ifndef __xe_sg_light__
#define __xe_sg_light__

#include "xe/Vector.hpp"
#include "xe/sg/Renderable.hpp"

namespace xe { namespace sg {

    enum class LightType {
        Global,
        Directional,
        Point,
        Spot
    };

    class Light : public Renderable {
    public:
        virtual ~Light() {}

        virtual void renderWith(Pipeline *renderer) override {
            renderer->render(this);
        }

    public:
        LightType type = LightType::Directional;

        // color information
        Vector4f ambient = Vector4f(0.1f, 0.1f, 0.1f, 1.0f);
        Vector4f diffuse = Vector4f(0.8f, 0.8f, 0.8f, 1.0f);
        Vector4f specular = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

        // geometry information
        Vector3f position = Vector3f(0.0f, 0.0f, 0.0f);
        Vector3f direction = Vector3f(0.0f, 0.0f, 1.0f);
        float range = 0.0f;
    };

    typedef std::unique_ptr<Light> LightPtr;
}}

#endif
