
#pragma once

#ifndef __xe_sg_scenerenderer__
#define __xe_sg_scenerenderer__

#include <memory>

#include "xe/sg/Scene.hpp"

namespace xe { namespace sg {
    
	class SceneRenderer {
    public:
        virtual void renderScene(Scene *scene) = 0;
	};

	typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
}}

#endif 
