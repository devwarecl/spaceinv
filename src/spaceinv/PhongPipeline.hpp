#pragma once

#include "xe/sg/Pipeline.hpp"
#include "gl3/Device.hpp"

class PhongPipeline : public xe::sg::Pipeline {
public:
	explicit PhongPipeline(gl3::Device *device);

	~PhongPipeline();

	virtual void beginFrame(const xe::Vector4f &color)override;
	virtual void endFrame()override;

	virtual void render(xe::sg::Light *light)override;
	virtual void render(xe::sg::Camera *camera)override;
	virtual void render(xe::sg::Geometry *geometry)override;
		
	virtual void setModel(const xe::Matrix4f &)override;

private:
	gl3::Device *m_device = nullptr;
};
