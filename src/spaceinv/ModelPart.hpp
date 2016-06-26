
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



struct ModelMaterial : public xe::gfx::Material {
	struct Attributes {
		xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
		xe::Vector4f diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
		xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
		xe::Vector4f emissive = {0.0f, 0.0f, 0.0f, 1.0f};
		float shininess = 0.0f;
		int tex_diffuse = 0;
	};

	Attributes attribs;

	explicit ModelMaterial(xe::gfx::UniformFormat *format) : Material(format) {
		flags.enable(xe::gfx::Material::CullFace);
		flags.enable(xe::gfx::Material::DepthTest);
		uniforms = &attribs;
	}
};

struct Patch {
    std::uint16_t start = 0;    // primera cara
    std::uint16_t count = 0;    // total de caras
};

struct ModelPart : public xe::sg::Geometry {
    xe::gfx::MeshFormat format;
    xe::gfx::MeshPtr mesh;
    size_t count = 0;

	xe::gfx::UniformFormat *materialFormat=nullptr;

    std::vector<ModelMaterial> materials;
    std::vector<Patch> patches;

    xe::gfx::Primitive primitive = xe::gfx::Primitive::TriangleList;
	
	virtual void renderWith(xe::sg::Pipeline *renderer) override {
		renderer->render(this);
	}
};

#endif 
