
#pragma once

#ifndef __xe_sg_scenemanagerimpl2_hpp__
#define __xe_sg_scenemanagerimpl2_hpp__

#include "xe/gfx/Device.hpp"

#include "SceneManager.hpp"

namespace xe { namespace sg {
    class SceneManagerImpl2 : public SceneManager {
    public:
        explicit SceneManagerImpl2(xe::gfx::Device *device);

        ~SceneManagerImpl2();

        virtual void renderScene(Scene *scene) override;

    private:
        std::vector<SceneNode*> linearizeNode(SceneNode *node);

    private:
        xe::gfx::Device *m_device = nullptr;
    };
}}

#endif
