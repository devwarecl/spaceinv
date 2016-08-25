
#pragma once

#ifndef __xe_sg_pipeline2base_hpp__
#define __xe_sg_pipeline2base_hpp__

#include "Pipeline2.hpp"

#include <map>

namespace xe { namespace sg {
    class Pipeline2Base : public Pipeline2 {
    public:
        Pipeline2Base();
        virtual ~Pipeline2Base();

        virtual void registerRenderer(const std::type_index &typeInfo, std::unique_ptr<Renderer> renderer) override;
        virtual std::unique_ptr<Renderer> unregisterRenderer(const std::type_index &typeInfo) override;

        virtual void render(Renderable *renderable) override;

    protected:
        std::map<std::type_index, std::unique_ptr<Renderer>> m_renderers;
    };
}}

#endif
