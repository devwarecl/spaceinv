
#pragma once

#ifndef __xe_sg_scenerenderer__
#define __xe_sg_scenerenderer__

#include <memory>

namespace xe { namespace sg {
    class Scene;
    class SceneManager {
    public:
        virtual ~SceneManager();

        virtual void renderScene(Scene *scene) = 0;
    };

    typedef std::unique_ptr<SceneManager> SceneManagerPtr;
}}

#endif 
