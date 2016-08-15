
#include "Pipeline2Base.hpp"

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
}}
