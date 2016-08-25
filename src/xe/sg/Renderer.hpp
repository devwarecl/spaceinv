
#pragma once

#ifndef __xe_sg_renderer_hpp__
#define __xe_sg_renderer_hpp__

#include <memory>

namespace xe { namespace sg {
    class Renderer;
    typedef std::unique_ptr<Renderer> RendererPtr;

    class Renderable;
    class Renderer {
    public:
        virtual ~Renderer();
        virtual void render(Renderable *renderable) = 0;
    };
}}

#endif
