
#pragma once

#ifndef __xe_sg_pipeline2_hpp__
#define __xe_sg_pipeline2_hpp__

#include <typeindex>
#include <memory>
#include <xe/Matrix.hpp>

namespace xe { namespace sg {
    class Renderable;
    class Renderer;
    class Pipeline2 {
    public:
        virtual ~Pipeline2();

        virtual void registerRenderer(const std::type_index &typeInfo, std::unique_ptr<Renderer> renderer) = 0;
        virtual std::unique_ptr<Renderer> unregisterRenderer(const std::type_index&typeInfo) = 0;

        virtual void setMatrix(const Matrix4f &matrix) = 0;

        virtual Matrix4f getMatrix() const = 0;

        virtual void render(Renderable *renderable) = 0;
    };
}}

#endif
