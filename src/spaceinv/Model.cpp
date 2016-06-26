
#include "Model.hpp"

Model::Model(std::vector<ModelPart> meshes) {
	m_meshes = std::move(meshes);
}

void Model::renderWith(xe::sg::Pipeline *pipeline) {
	this->renderWith(dynamic_cast<PhongPipeline*>(pipeline));
}

void Model::renderWith(PhongPipeline *pipeline) {
	assert(pipeline);
	assert(m_meshes.size() > 0);

	pipeline->render(&m_meshes[0]);
}
