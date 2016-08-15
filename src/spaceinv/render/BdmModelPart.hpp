
#ifndef __mesh__
#define __mesh__

#include <vector>
#include "xe/Vector.hpp"
#include "xe/sg/Renderable.hpp"
#include "xe/sg/Geometry.hpp"
#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/Primitive.hpp"
#include "xe/gfx/Texture.hpp"
#include "xe/gfx/Mesh.hpp"

#include "PhongMaterial.hpp"

struct Box {
    xe::Vector3f pmin;
    xe::Vector3f pmax;

    xe::Vector3f size() const {
        return pmax - pmin;
    }

    xe::Vector3f center() const {
        return pmin + size() * 0.5f;
    }
};

struct Patch {
    std::uint16_t start = 0;    // primera cara
    std::uint16_t count = 0;    // total de caras
};

struct BdmModelPart : public xe::sg::Geometry {
    xe::gfx::MeshFormat format;
    xe::gfx::MeshPtr mesh;
    size_t count = 0;

    xe::gfx::UniformFormat *materialFormat=nullptr;

    std::vector<PhongMaterial> materials;
    std::vector<Patch> patches;

    xe::gfx::Primitive primitive = xe::gfx::Primitive::TriangleList;
    
    virtual void renderWith(xe::sg::Pipeline *renderer) override;
};

#endif 
