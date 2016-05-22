
#pragma once 

#ifndef __xe_sg_scenerenderergeneric__
#define __xe_sg_scenerenderergeneric__

#include "xe/sg/Pipeline.hpp"
#include "xe/sg/SceneRenderer.hpp"
#include "xe/sg/TransformationStack.hpp"

namespace xe { namespace sg {
	class SceneRendererImpl : public SceneRenderer {
	public:
		explicit SceneRendererImpl(Scene *scene, Pipeline *renderer) : SceneRenderer(scene) {
		    m_renderer = renderer;
	    }

		virtual ~SceneRendererImpl() {}

		virtual void renderScene() override;

	protected:
		void renderNode(xe::sg::TransformationStack *transformStack, xe::sg::SceneNode* node);

		Pipeline* m_renderer = nullptr;
	};
}}

#endif
