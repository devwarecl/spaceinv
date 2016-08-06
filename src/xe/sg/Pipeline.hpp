
#pragma once

#ifndef __xe_sg_pipeline_hpp__
#define __xe_sg_pipeline_hpp__

#include <memory>

#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
#include "xe/sg/Forward.hpp"

namespace xe { namespace sg {
    class Pipeline {
    public:
        virtual ~Pipeline();
        
        virtual void beginFrame(const xe::Vector4f &color) = 0;
        virtual void endFrame() = 0;

        virtual void render(xe::sg::Light *light) = 0;
        virtual void render(xe::sg::Camera *camera) = 0;
        virtual void render(xe::sg::Geometry *geometry) = 0;
        
        virtual void setWorldTransform(const xe::Matrix4f &) = 0;
    };

    typedef std::unique_ptr<Pipeline> PipelinePtr;
}}

#endif 
