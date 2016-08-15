
#include "BdmModel.hpp"

BdmModel::BdmModel(std::vector<BdmModelPart> parts) {
    m_parts = std::move(parts);
}

void BdmModel::renderWith(xe::sg::Pipeline *pipeline) {
    this->renderWith(dynamic_cast<PhongPipeline*>(pipeline));
}

void BdmModel::renderWith(PhongPipeline *pipeline) {
    assert(pipeline);
    assert(m_parts.size() > 0);

    pipeline->render(&m_parts[0]);
}
