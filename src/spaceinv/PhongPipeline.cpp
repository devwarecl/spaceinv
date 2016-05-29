
#include "PhongPipeline.hpp"

PhongPipeline::PhongPipeline(gl3::Device *device) {
	m_device = device;
}

PhongPipeline::~PhongPipeline() {}

void PhongPipeline::beginFrame(const xe::Vector4f &color) {

}
void PhongPipeline::endFrame() {

}

void PhongPipeline::render(xe::sg::Light *light) {

}

void PhongPipeline::render(xe::sg::Camera *camera) {

}

void PhongPipeline::render(xe::sg::Geometry *geometry) {

}
		
void PhongPipeline::setModel(const xe::Matrix4f &) {

}
