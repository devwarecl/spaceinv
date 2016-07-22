
#pragma once

#ifndef __xe_sg_geometry__
#define __xe_sg_geometry__

#include <memory>
#include "xe/Boundary.hpp"
#include "xe/sg/Renderable.hpp"
#include "xe/sg/Pipeline.hpp"

namespace xe { namespace sg {
    
    class Geometry : public Renderable {
    public:
        virtual ~Geometry() {}

        virtual void renderWith(Pipeline *renderer) override {
            assert(renderer);
            renderer->render(this);
        }
    };

    typedef std::unique_ptr<Geometry> GeometryPtr;
}}

#endif 
