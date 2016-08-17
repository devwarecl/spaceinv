
#include "SceneManagerImpl2.hpp"

namespace xe { namespace sg {
    SceneManagerImpl2::SceneManagerImpl2(xe::gfx::Device *device) 
        : m_device(device) {}

    SceneManagerImpl2::~SceneManagerImpl2() {}

    struct RenderEntry {
        Matrix4f transformation = identity<float, 4>();
        Renderable *renderable = nullptr;
    };

    static std::vector<RenderEntry> getRenderEntries(SceneNode *node) {
        assert(node);

        std::vector<RenderEntry> entries;

        for (int i=0; i<node->getChildCount(); i++) {
            SceneNode* child = node->getChild(i);

            nodes.push_back(child);

            auto linearizedChilds = this->getRenderEntries(child);

            nodes.insert(nodes.end(), linearizedChilds.begin(), linearizedChilds.end());
        }

        return entries;
    }

    void SceneManagerImpl2::renderScene(Scene *scene) {
        auto nodes = this->linearizeNode(scene->getNode());

        for (auto &node : nodes) {
            
        }
    }
}}
