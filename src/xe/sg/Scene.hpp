
#pragma once

#ifndef __xe_sg_scene_hpp__
#define __xe_sg_scene_hpp__

#include <memory>
#include "xe/Vector.hpp"
#include "xe/sg/SceneNode.hpp"

namespace xe { namespace sg {
    class Scene {
    public:
        Scene();
        ~Scene();

        const SceneNode* getNode() const {
            return &m_rootNode;
        }

        SceneNode* getNode() {
            return &m_rootNode;
        }

        Vector4f getBackColor() const {
            return m_backcolor;
        }

        Scene* setBackColor(const Vector4f &color) {
            m_backcolor = color;

            return this;
        }

    private:
        Vector4f m_backcolor = {0.2f, 0.2f, 0.2f, 1.0f};
        SceneNode m_rootNode;
    };

    typedef std::unique_ptr<Scene> ScenePtr;
}}

#endif
