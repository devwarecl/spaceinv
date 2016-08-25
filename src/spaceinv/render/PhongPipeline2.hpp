
#pragma once

#ifndef __spaceinv_phongpipeline2_hpp__
#define __spaceinv_phongpipeline2_hpp__

#include <xe/gfx/Device.hpp>
#include <xe/sg/Pipeline2Base.hpp>

namespace spaceinv {
    class PhongPipeline2 : public xe::sg::Pipeline2Base {
    public:
        explicit PhongPipeline2(xe::gfx::Device *device); 
        
        virtual ~PhongPipeline2();

        virtual void setMatrix(const xe::Matrix4f &matrix) override {
            m_world = matrix;
        }

        virtual xe::Matrix4f getMatrix() const override {
            return m_world;
        }

    private:
        xe::gfx::Device *m_device = nullptr;
        xe::gfx::ProgramPtr m_program;
        xe::Matrix4f m_proj;
        xe::Matrix4f m_view;
        xe::Matrix4f m_world;
    };
}

#endif
