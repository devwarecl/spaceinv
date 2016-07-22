
#include "Model.hpp"

Model::Model(std::vector<ModelPart> parts) {
    m_parts = std::move(parts);
}

void Model::renderWith(xe::sg::Pipeline *pipeline) {
    this->renderWith(dynamic_cast<PhongPipeline*>(pipeline));
}

void Model::renderWith(PhongPipeline *pipeline) {
    assert(pipeline);
    assert(m_parts.size() > 0);

    pipeline->render(&m_parts[0]);
}
