

#ifndef __xe_sg_renderer_hpp__
#define __xe_sg_renderer_hpp__

namespace xe { namespace sg {
    class Renderable;
    class Renderer {
    public:
        virtual ~Renderer();
        virtual void render(Renderable *renderable) = 0;
    };
}}

#endif
