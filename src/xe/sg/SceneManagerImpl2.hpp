
#pragma once

#ifndef __xe_sg_scenemanagerimpl2_hpp__
#define __xe_sg_scenemanagerimpl2_hpp__

#include "SceneManager.hpp"

namespace xe { namespace sg {
    class Pipeline2;

    class SceneManagerImpl2 : public SceneManager {
    public:
        explicit SceneManagerImpl2(xe::sg::Pipeline2 *pipeline);

        ~SceneManagerImpl2();

        virtual void renderScene(Scene *scene) override;

    private:
        xe::sg::Pipeline2 *m_pipeline = nullptr;
    };
}}

#endif
