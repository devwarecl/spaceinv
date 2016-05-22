/**
 * @file ISceneRenderer.hpp
 * @brief Definition of the ISceneRenderer interface.
 */


/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __xe_sg_scenerenderer__
#define __xe_sg_scenerenderer__

#include <memory>

#include "xe/sg/Scene.hpp"

namespace xe { namespace sg {
    
	class SceneRenderer {
    public:
        explicit SceneRenderer(Scene *scene) {
            assert(scene);

            m_scene = scene;
        }

        virtual void renderScene() = 0;

    protected:
        Scene *m_scene = nullptr;
	};

	typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
}}

#endif 
