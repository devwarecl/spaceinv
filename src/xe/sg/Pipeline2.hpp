
#pragma once

#ifndef __xe_sg_pipeline2_hpp__
#define __xe_sg_pipeline2_hpp__

#include "Renderable.hpp"
#include <typeinfo>

namespace xe { namespace sg {

    class Renderer {
    public:
        virtual ~Renderer() {}
        virtual void render(Renderable *renderable) = 0;
    };

    class Pipeline2 {
    public:
        virtual ~Pipeline2() {}

        virtual void registerRenderer(const std::type_info &typeInfo, Renderer *renderer) = 0;
        virtual void unregisterRenderer(const std::type_info &typeInfo) = 0;

        virtual void render(Renderable *renderable) = 0;
    };
}}

#endif
