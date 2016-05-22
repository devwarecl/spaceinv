
#include "SceneRendererGeneric.hpp"

#include <cassert>
#include <xe/sg/Scene.hpp>
#include <xe/sg/SceneNode.hpp>
#include <xe/sg/Renderable.hpp>

namespace xe { namespace sg {

	void SceneRendererImpl::renderScene() {
		assert(m_scene);
        assert(m_renderer);

		TransformationStack transformStack;

		transformStack.reset(xe::identity<float, 4>());

		m_renderer->beginFrame(m_scene->backcolor);
		this->renderNode(&transformStack, &m_scene->rootNode);
		m_renderer->endFrame();
	}

	void SceneRendererImpl::renderNode(TransformationStack *transformStack, SceneNode* node) {
        assert(transformStack);
		assert(node);

		transformStack->push(node->transform);
        
		m_renderer->setModel(transformStack->top());

		if (node->renderable) {
			node->renderable->renderWith(m_renderer);
		}

        for (auto &child : node->childs) {
            this->renderNode(transformStack, &child);
        }

		transformStack->pop();
	}
}}
