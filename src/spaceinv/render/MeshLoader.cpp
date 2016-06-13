
#include "MeshLoader.hpp"
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

std::vector<Material> createMaterialArray(TextureLoader &loader, const bdm::Mesh &bdm_mesh) {
    std::vector<Material> materials;

    for (const auto &textureName : bdm_mesh.textures) {
        Material material;
        material.texture = loader.loadTexture(textureName);

        materials.push_back(std::move(material));
    }

    return materials;
}

std::vector<xe::Vector2f> createTexCoordArray(const std::vector<Material> &materials, const bdm::Mesh &bdm_mesh) {
    std::vector<xe::Vector2f> texcoords;

    // Procesar mapeo de texturas
    for (size_t i=0; i<bdm_mesh.texcoords.size(); i++) {
        const auto &t = bdm_mesh.texcoords[i];
        const auto mindex = bdm_mesh.texturefaces[i / 3];
        const auto &material = materials[mindex];

        xe::Vector2f texsize = {1.0f, 1.0f};
        
        if (material.texture) {
            texsize = material.texture->getSize()/* - xe::Vector2f(1.0f, 1.0f)*/;
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

    std::cout << "Patch " << (mindex) << ". (" << patch.start << ", " << patch.count << ")" << std::endl;

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

Mesh createMesh(const bdm::Mesh &bdm_mesh, const gl3::MeshFormat &format, TextureLoader *loader) {    
    auto materials = createMaterialArray(*loader, bdm_mesh);
    auto vertices = createVertexArray(bdm_mesh);
    auto normals = generateNormals(vertices);
    auto texcoords = createTexCoordArray(materials, bdm_mesh);
    auto patches = createPatchArray(bdm_mesh);

    scale(getBox(vertices), vertices);

    // cargar datos a OpenGL
    gl3::BufferVector buffers;
    buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices));
    buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, normals));
    buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, texcoords));
    
    // finalizar construccion modelo
    Mesh mesh;

    mesh.count = vertices.size();
    mesh.primitive = GL_TRIANGLES;
    mesh.subset = std::make_unique<gl3::Mesh>(format, std::move(buffers));
    mesh.materials = std::move(materials);
    mesh.patches = std::move(patches);
    mesh.format = format;
    
    return mesh;
}

std::vector<Mesh> MeshLoader::createMeshSet(const std::string &path, const gl3::MeshFormat &format) {
    std::vector<Mesh> meshes;

	std::string location = path;
	if (m_locator) {
		location = m_locator->locate(path);
	}

    bdm::BdmFile bdm_file(location.c_str());
    
    for (auto &bdm_mesh : bdm_file.meshes()) {
        meshes.push_back(createMesh(bdm_mesh, format, m_textureLoader));
    }

    return meshes;
}
