
#pragma once

#include "xe/sg/Renderable.hpp"
#include "render/PhongPipeline.hpp"

#include "ModelPart.hpp"

class Model : public xe::sg::Renderable {
public:
	explicit Model(std::vector<ModelPart> parts);

	virtual void renderWith(xe::sg::Pipeline *pipeline) override;

	virtual void renderWith(PhongPipeline *pipeline);

private:
	std::vector<ModelPart> m_parts;
};

typedef std::unique_ptr<Model> ModelPtr;
