
#include "ModelLoader.hpp"
#include "bdm/BdmFile.hpp"

std::vector<xe::Vector3f> createVertexArray(const bdm::Mesh &bdm_mesh) {
    std::vector<xe::Vector3f> vertices;

    for (auto &face : bdm_mesh.faces) {
        for (auto index : face.values) {
            auto vertex = xe::Vector3f(bdm_mesh.vertices[index].values);
            vertices.push_back(vertex);
        }
    }

    return vertices;
}

Box getBox(const std::vector<xe::Vector3f> &vertices) {
    Box box;

    box.pmin = vertices[0];
    box.pmax = vertices[0];

    for (size_t i=0; i<vertices.size(); i++) {
        box.pmin = xe::minimize(box.pmin, vertices[i]);
        box.pmax = xe::maximize(box.pmax, vertices[i]);
    }

    return box;
}

std::vector<xe::Vector3f> generateNormals(const std::vector<xe::Vector3f> &vertices) {
    std::vector<xe::Vector3f> normals;

    for (size_t i=0; i<vertices.size(); i+=3) {

        // generar normales
        auto v1 = vertices[i + 1] - vertices[i + 0];
        auto v2 = vertices[i + 2] - vertices[i + 0];

        auto n = xe::normalize(xe::cross(v2, v1));

        for (int j=0; j<3; j++) {
            normals.push_back(n);
        }
    }

    return normals;
}

void scale(const Box &scaleBox, std::vector<xe::Vector3f> &vertices) {
    auto center = scaleBox.center();
    auto length = xe::max(scaleBox.size());

    // post procesar modelo
    for (size_t i=0; i<vertices.size(); i+=3) {

        // escalar modelo
        for (int j=0; j<3; j++) {
            vertices[i + j] -= center;
            vertices[i + j] *= 5.0f/length;
        }
    }
}

std::vector<ModelMaterial> createMaterialArray(xe::gfx::UniformFormat *format, TextureLoader &loader, const bdm::Mesh &bdm_mesh) {
    std::vector<ModelMaterial> materials;

    for (const auto &textureName : bdm_mesh.textures) {
        ModelMaterial material(format);

        xe::gfx::Texture *texture = loader.loadTexture(textureName);
		material.layers.push_back(xe::gfx::MaterialLayer(texture));

        materials.push_back(std::move(material));
    }

    return materials;
}

std::vector<xe::Vector2f> createTexCoordArray(const std::vector<ModelMaterial> &materials, const bdm::Mesh &bdm_mesh) {
    std::vector<xe::Vector2f> texcoords;

    // Procesar mapeo de texturas
    for (size_t i=0; i<bdm_mesh.texcoords.size(); i++) {
        const auto &t = bdm_mesh.texcoords[i];
        const auto mindex = bdm_mesh.texturefaces[i / 3];
        const auto &material = materials[mindex];

        xe::Vector2f texsize = {1.0f, 1.0f};
        
        if (material.layers[0].texture) {
			auto desc = material.layers[0].texture->getDesc();

            texsize.x = float(desc.width);
			texsize.y = float(desc.height);
        }

        xe::Vector2f texcoord = xe::Vector2f(t.values) / texsize;

        texcoords.push_back(texcoord);
    }

    return texcoords;
}

Patch createPatch(const bdm::Mesh &bdm_mesh, const uint16_t mindex) {

    auto &tfaces = bdm_mesh.texturefaces;

    auto itfirst = std::find(std::begin(tfaces), std::end(tfaces), mindex);
    auto itlast = std::find(std::rbegin(tfaces), std::rend(tfaces), mindex);

    uint16_t first = std::distance(std::begin(tfaces), itfirst);
    uint16_t last = std::distance(itlast, std::rend(tfaces));

    Patch patch;

    patch.start = 3 * first;
    patch.count = 3 * (last - first);

    return patch;
}

std::vector<Patch> createPatchArray(const bdm::Mesh &bdm_mesh) {
    std::vector<Patch> patches;

    for (uint16_t mindex=0; mindex<bdm_mesh.textures.size(); mindex++) {
        Patch patch = createPatch(bdm_mesh, mindex);

        patches.push_back(patch);
    }

    return patches;
}

ModelPart createPart(const bdm::Mesh &bdm_mesh, xe::gfx::UniformFormat *materialFormat, const xe::gfx::MeshFormat &format, TextureLoader *loader, xe::gfx::Device *device) {    
    auto materials = createMaterialArray(materialFormat, *loader, bdm_mesh);
    auto vertices = createVertexArray(bdm_mesh);
    auto normals = generateNormals(vertices);
    auto texcoords = createTexCoordArray(materials, bdm_mesh);
    auto patches = createPatchArray(bdm_mesh);

    scale(getBox(vertices), vertices);

	// cargar datos a OpenGL
	std::vector<xe::BufferPtr> buffers;

	buffers.push_back(device->createBuffer(xe::gfx::BufferType::Vertex, vertices));
	buffers.push_back(device->createBuffer(xe::gfx::BufferType::Vertex, normals));
	buffers.push_back(device->createBuffer(xe::gfx::BufferType::Vertex, texcoords));

    //buffers.emplace_back(new xe::gfx::gl3::BufferGL(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices));
    //buffers.emplace_back(new xe::gfx::gl3::BufferGL(GL_ARRAY_BUFFER, GL_STATIC_DRAW, normals));
    //buffers.emplace_back(new xe::gfx::gl3::BufferGL(GL_ARRAY_BUFFER, GL_STATIC_DRAW, texcoords));
    
    // finalizar construccion modelo
    ModelPart part;

    part.count = vertices.size();
    part.primitive = xe::gfx::Primitive::TriangleList;
    part.mesh = device->createMesh(format, std::move(buffers));
    part.materials = std::move(materials);
    part.patches = std::move(patches);
    part.format = format;
	part.materialFormat = materialFormat;
    
    return part;
}

ModelPtr ModelLoader::createModel(const std::string &path, xe::gfx::UniformFormat *materialFormat, const xe::gfx::MeshFormat &format) {
    std::vector<ModelPart> parts;

	std::string location = path;
	if (m_locator) {
		location = m_locator->locate(path);
	}

    bdm::BdmFile bdm_file(location.c_str());
    
    for (auto &bdm_mesh : bdm_file.meshes()) {
        parts.push_back(createPart(bdm_mesh, materialFormat, format, m_textureLoader, m_device));
    }

    return std::make_unique<Model>(std::move(parts));
}

Model* ModelLoader::getModel(const std::string &name, xe::gfx::UniformFormat *materialFormat, const xe::gfx::MeshFormat *format) {
	Model* model = nullptr;

	auto modelIt = m_models.find(name);

	if (modelIt == std::end(m_models)) {
		m_models[name] = this->createModel(name, materialFormat, *format);
		model = m_models[name].get();

	} else {
		model = modelIt->second.get();
	}

	return model;
}
