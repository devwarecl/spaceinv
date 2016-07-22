
#include "SceneRendererImpl.hpp"

#include <cassert>
#include "xe/sg/Scene.hpp"
#include "xe/sg/SceneNode.hpp"
#include "xe/sg/Renderable.hpp"

namespace xe { namespace sg {

    void SceneRendererImpl::renderScene(Scene *scene) {
        assert(m_pipeline);
        assert(scene);
        
        TransformationStack transformStack;

        transformStack.reset(xe::identity<float, 4>());

        m_pipeline->beginFrame(scene->backcolor);
        this->renderNode(&transformStack, &scene->rootNode);
        m_pipeline->endFrame();
    }

    void SceneRendererImpl::renderNode(TransformationStack *transformStack, SceneNode* node) {
        assert(transformStack);
        assert(node);

        transformStack->push(node->transform);
        
        m_pipeline->setWorldTransform(transformStack->top());

        if (node->renderable) {
            node->renderable->renderWith(m_pipeline);
        }

        for (auto &child : node->childs) {
            this->renderNode(transformStack, child.get());
        }

        transformStack->pop();
    }
}}
