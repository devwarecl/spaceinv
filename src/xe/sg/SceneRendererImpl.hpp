
#pragma once 

#ifndef __xe_sg_scenerendererimpl__
#define __xe_sg_scenerendererimpl__

#include "xe/sg/Pipeline.hpp"
#include "xe/sg/SceneRenderer.hpp"
#include "xe/sg/TransformationStack.hpp"

namespace xe { namespace sg {
    class SceneRendererImpl : public SceneRenderer {
    public:
        explicit SceneRendererImpl(Pipeline* pipeline) {
            m_pipeline = pipeline;
        }

        virtual ~SceneRendererImpl() {}

        virtual void renderScene(Scene *scene) override;

    protected:
        void renderNode(xe::sg::TransformationStack *transformStack, xe::sg::SceneNode* node);

        Pipeline* m_pipeline = nullptr;
    };
}}

#endif
