
#include "SceneManagerImpl.hpp"

#include <cassert>
#include "xe/sg/Scene.hpp"
#include "xe/sg/SceneNode.hpp"
#include "xe/sg/Renderable.hpp"

namespace xe { namespace sg {

    void SceneManagerImpl::renderScene(Scene *scene) {
        assert(m_pipeline);
        assert(scene);
        
        TransformationStack transformStack;

        transformStack.reset(xe::identity<float, 4>());

        m_pipeline->beginFrame(scene->getBackColor());
        this->renderNode(&transformStack, scene->getNode());
        m_pipeline->endFrame();
    }

    void SceneManagerImpl::renderNode(TransformationStack *transformStack, SceneNode* node) {
        assert(transformStack);
        assert(node);

        transformStack->push(node->getMatrix());
        
        m_pipeline->setWorldTransform(transformStack->top());

        if (node->getRenderable()) {
            node->getRenderable()->renderWith(m_pipeline);
        }

        for (std::size_t i=0; i<node->getChildCount(); i++) {
            this->renderNode(transformStack, node->getChild(i));
        }

        transformStack->pop();
    }
}}
