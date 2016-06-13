
#ifndef __mesh__
#define __mesh__

#include <vector>
#include "xe/Vector.hpp"
#include "xe/sg/Renderable.hpp"
#include "xe/sg/Geometry.hpp"
#include "gl3/Texture.hpp"
#include "gl3/Subset.hpp"

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

struct Material {
    bool cullface = true;

    xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
    xe::Vector4f diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
    xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
    xe::Vector4f emissive = {0.0f, 0.0f, 0.0f, 1.0f};

    float shininess = 0.0f;

    gl3::TexturePtr texture;
};

struct Patch {
    std::uint16_t start = 0;    // primera cara
    std::uint16_t count = 0;    // total de caras
};

struct Mesh : public xe::sg::Geometry {
    gl3::MeshFormat format;
    gl3::MeshPtr subset;
    size_t count = 0;

    std::vector<Material> materials;
    std::vector<Patch> patches;

    GLenum primitive = GL_TRIANGLES;
	
	virtual void renderWith(xe::sg::Pipeline *renderer) override {
		renderer->render(this);
	}
};

#endif 
