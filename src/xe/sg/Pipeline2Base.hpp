
#pragma once

#ifndef __xe_sg_pipeline2base_hpp__
#define __xe_sg_pipeline2base_hpp__

#include "Pipeline2.hpp"

#include <map>

namespace xe { namespace sg {
    class Pipeline2Base : public Pipeline2 {
    public:
        Pipeline2Base();
        ~Pipeline2Base();

        virtual void registerRenderer(const std::type_index &typeInfo, Renderer *renderer) override;
        virtual void unregisterRenderer(const std::type_index &typeInfo) override;

    protected:
        std::map<std::type_index, Renderer*> m_renderers;
    };
}}

#endif
