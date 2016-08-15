
#pragma once

#include "xe/sg/Renderable.hpp"
#include "PhongPipeline.hpp"
#include "BdmModelPart.hpp"

class BdmModel : public xe::sg::Renderable {
public:
    explicit BdmModel(std::vector<BdmModelPart> parts);

    virtual void renderWith(xe::sg::Pipeline *pipeline) override;

    virtual void renderWith(PhongPipeline *pipeline);

private:
    std::vector<BdmModelPart> m_parts;
};

typedef std::unique_ptr<BdmModel> ModelPtr;
