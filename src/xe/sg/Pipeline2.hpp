
#pragma once

#ifndef __xe_sg_pipeline2_hpp__
#define __xe_sg_pipeline2_hpp__

#include <typeindex>

namespace xe { namespace sg {
    class Renderable;
    class Renderer;
    class Pipeline2 {
    public:
        virtual ~Pipeline2();

        virtual void registerRenderer(const std::type_index &typeInfo, Renderer *renderer) = 0;
        virtual void unregisterRenderer(const std::type_index&typeInfo) = 0;

        virtual void render(Renderable *renderable) = 0;
    };
}}

#endif
