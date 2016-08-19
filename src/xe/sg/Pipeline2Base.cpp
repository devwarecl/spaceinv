
#include "Pipeline2Base.hpp"

#include <xe/sg/Renderer.hpp>
#include <cassert>

#if defined(_DEBUG)
#include <iostream>
#endif

namespace xe { namespace sg {

    Pipeline2Base::Pipeline2Base() {}

    Pipeline2Base::~Pipeline2Base() {}

    void Pipeline2Base::registerRenderer(const std::type_index &typeInfo, Renderer *renderer) {
        m_renderers[typeInfo] = renderer;
    }

    void Pipeline2Base::unregisterRenderer(const std::type_index &typeInfo) {
        auto pos = m_renderers.find(typeInfo);

        if (pos != m_renderers.end()) {
            m_renderers.erase(pos);
        }
    }

    void Pipeline2Base::render(Renderable *renderable) {
        assert(false);

        auto pos = m_renderers.find(std::type_index(typeid(renderable)));

#if defined(_DEBUG)
        if (pos == m_renderers.end()) {
            std::cerr << "Pipeline2Base::render: Unknown renderable implementation: " << typeid(renderable).name() << std::endl;
        }
#endif
        pos->second->render(renderable);
    }
}}
