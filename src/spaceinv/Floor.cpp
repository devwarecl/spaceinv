
#include "Floor.hpp"
#include "render/PhongMaterial.hpp"
#include "render/PhongPipeline.hpp"

Floor::Floor(xe::gfx::UniformFormat *format, xe::gfx::Mesh *mesh, int count) {
    assert(format);
    assert(mesh);

    m_mesh = mesh;
    m_material = std::make_unique<PhongMaterial>(format);
    m_count = count;
}

Floor::~Floor() {}

void Floor::renderWith(xe::sg::Pipeline *pipeline_) {
    assert(pipeline_);
    
    auto pipeline = dynamic_cast<PhongPipeline*>(pipeline_);
    auto device = pipeline->getDevice();

    device->setMaterial(m_material.get());
    device->setMesh(m_mesh);
    device->render(xe::gfx::Primitive::TriangleList, 0, m_count);
}
