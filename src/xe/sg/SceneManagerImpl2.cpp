
#include "SceneManagerImpl2.hpp"

#include <vector>
#include <xe/sg/Pipeline2.hpp>
#include <xe/sg/Renderable.hpp>
#include <xe/sg/Scene.hpp>

namespace xe { namespace sg {

    SceneManagerImpl2::SceneManagerImpl2(xe::sg::Pipeline2 *pipeline) 
        : m_pipeline(pipeline) {}

    SceneManagerImpl2::~SceneManagerImpl2() {}

    struct RenderEntry {
        Matrix4f matrix = identity<float, 4>();
        Renderable *renderable = nullptr;

        RenderEntry() {}

        RenderEntry(Matrix4f matrix_, Renderable *renderable_) 
            : matrix(matrix_), renderable(renderable_) {}
    };

    typedef std::vector<RenderEntry> RenderEntryArray;

    /**
     * @brief Merge a std::vector into another
     */
    template<typename Type>
    void merge(std::vector<Type> &to, const std::vector<Type> &from) {
        const size_t to_size = to.size();
        const size_t from_size = from.size();
        
        to.resize(to_size + from_size);

        for (size_t i=0; i<from_size; i++) {
            to[to_size + i] = from[i];
        }
    }

    /**
     * @brief Grab a Scene Hierarchy a linearizes it
     */
    static RenderEntryArray linearizeNode(SceneNode *node, const Matrix4f &parentMatrix = identity<float, 4>()) {
        assert(node);

        const Matrix4f matrix = parentMatrix * node->getMatrix();
        
        RenderEntryArray entries;
        
        if (node->getRenderable()) {
            entries.push_back({matrix, node->getRenderable()});
        }

        for (int i=0; i<node->getChildCount(); i++) {
            RenderEntryArray childEntries = linearizeNode(node->getChild(i), matrix);

            for (const RenderEntry &childEntry : childEntries) {
                entries.push_back(childEntry);
            }
        }

        return entries;
    }

    void SceneManagerImpl2::renderScene(Scene *scene) {
        assert(scene);

        RenderEntryArray entries = linearizeNode(scene->getNode());

        for (const RenderEntry entry : entries) {
            m_pipeline->setMatrix(entry.matrix);
            m_pipeline->render(entry.renderable);
        }
    }
}}
