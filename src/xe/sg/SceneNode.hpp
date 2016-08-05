
#pragma once

#ifndef __xe_sg_scenenode__
#define __xe_sg_scenenode__

#include <vector>
#include <memory>

#include "xe/Matrix.hpp"
#include "xe/sg/Forward.hpp"

namespace xe { namespace sg {
    class SceneNode;
    typedef std::unique_ptr<SceneNode> SceneNodePtr;
    
    class SceneNode {
    public:
        SceneNode();
        ~SceneNode();

        SceneNode* addChild() {
            auto* node = new SceneNode();

            m_childs.emplace_back(node);

            return node;
        }

        SceneNode* setName(const std::string &name) {
            m_name = name;
            return this;
        }

        SceneNode* setRenderable(Renderable *renderable) {
            m_renderable = renderable;
            return this;
        }

        SceneNode* setMatrix(const Matrix4f &matrix) {
            m_matrix = matrix;
            return this;
        }

        std::string getName() const {
            return m_name;
        }

        Renderable* getRenderable() const {
            return m_renderable;
        }

        Matrix4f getMatrix() const {
            return m_matrix;
        }

        std::size_t getChildCount() const {
            return m_childs.size();
        }

        SceneNode* getChild(const std::size_t index) const {
            return m_childs[index].get();
        }

    private:
        std::string m_name;
        Renderable *m_renderable = nullptr;
        Matrix4f m_matrix = xe::identity<float, 4>();
        
        std::vector<SceneNodePtr> m_childs;
    };
}}

#endif
