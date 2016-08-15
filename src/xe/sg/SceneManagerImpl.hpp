
#pragma once 

#ifndef __xe_sg_scenerendererimpl__
#define __xe_sg_scenerendererimpl__

#include "xe/sg/Pipeline.hpp"
#include "xe/sg/SceneManager.hpp"
#include "xe/sg/TransformationStack.hpp"

namespace xe { namespace sg {
    class SceneManagerImpl : public SceneManager {
    public:
        explicit SceneManagerImpl(Pipeline* pipeline) {
            m_pipeline = pipeline;
        }

        virtual ~SceneManagerImpl() {}

        virtual void renderScene(Scene *scene) override;

    protected:
        void renderNode(xe::sg::TransformationStack *transformStack, xe::sg::SceneNode* node);

        Pipeline* m_pipeline = nullptr;
    };
}}

#endif
