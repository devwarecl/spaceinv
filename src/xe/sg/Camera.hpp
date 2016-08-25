
#pragma once

#ifndef __xe_sg_camera__
#define __xe_sg_camera__

#include <memory>

#include "xe/Matrix.hpp"
#include "xe/Rect.hpp"
#include "xe/sg/Renderable.hpp"
#include "xe/sg/Pipeline.hpp"

namespace xe { namespace sg {

    class Camera : public Renderable {
    public:
        virtual ~Camera() {}

        virtual Matrix4f computeView() const = 0;
        virtual Matrix4f computeProj() const = 0;

        virtual Rectf getViewport() const = 0;

        virtual void renderWith(xe::sg::Pipeline *renderer) override {
            assert(renderer);

            renderer->render(this);
        }
    };

    typedef std::unique_ptr<Camera> CameraPtr;
}}

#endif
