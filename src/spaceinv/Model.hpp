
#pragma once

#include "xe/sg/Renderable.hpp"
#include "render/PhongPipeline.hpp"

class Model : public xe::sg::Renderable {
public:
	explicit Model(std::vector<Mesh> meshes);

	virtual void renderWith(xe::sg::Pipeline *pipeline) override;

	virtual void renderWith(PhongPipeline *pipeline);

private:
	std::vector<Mesh> m_meshes;
};

typedef std::unique_ptr<Model> ModelPtr;
