#pragma once

#ifndef __phongpipeline__
#define __phongpipeline__

#include "xe/sg/Pipeline.hpp"
#include "xe/gfx/Device.hpp"
#include "xe/gfx/Program.hpp"

#include "../ModelPart.hpp"

class PhongPipeline : public xe::sg::Pipeline {
public:
    explicit PhongPipeline(xe::gfx::Device *device);

    ~PhongPipeline();

    virtual void beginFrame(const xe::Vector4f &color) override;
    virtual void endFrame() override;

    virtual void render(xe::sg::Light *light) override;
    virtual void render(xe::sg::Camera *camera) override;
    virtual void render(xe::sg::Geometry *geometry) override;
    
    void render(ModelPart *mesh);

    virtual void setWorldTransform(const xe::Matrix4f &world) override;

    xe::gfx::Device *getDevice() {
        return m_device;
    }

protected:
    xe::Matrix4f getPVW() const;

    void renderMesh(ModelPart &mesh);

    void updateMvp();

private:
    xe::gfx::Device *m_device = nullptr;
    xe::gfx::ProgramPtr m_program;

    xe::Matrix4f m_proj;
    xe::Matrix4f m_view;
    xe::Matrix4f m_world;
};

typedef std::unique_ptr<PhongPipeline> PhongPipelinePtr;

#endif
