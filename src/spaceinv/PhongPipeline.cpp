
#include <fstream>
#include "PhongPipeline.hpp"

#include "xe/sg/Camera.hpp"

std::string loadTextFile(const std::string &file) {
    std::fstream fs;

    fs.open(file.c_str(), std::ios_base::in);
    if (!fs.is_open()) {
        throw std::runtime_error("");
    }

    std::string content;

    while (!fs.eof()) {
        std::string line;
        std::getline(fs, line);

        content += line + "\n";
    }

    return content;
}

PhongPipeline::PhongPipeline(gl3::Device *device) {
	assert(device);

	m_device = device;

	// inicializar las matrices por defecto
	m_proj = xe::identity<float, 4>();
    m_view = xe::identity<float, 4>();
    m_world = xe::identity<float, 4>();

	// programa shader
	std::string vshader = loadTextFile("assets/shaders/vertex.glsl");
	std::string fshader = loadTextFile("assets/shaders/fragment.glsl");

	gl3::ShaderVector shaders;
	shaders.emplace_back(new gl3::Shader (GL_VERTEX_SHADER, vshader));
	shaders.emplace_back(new gl3::Shader (GL_FRAGMENT_SHADER, fshader));

	m_program = std::make_unique<gl3::Program>(std::move(shaders));

	m_device->setProgram(m_program.get());
}

PhongPipeline::~PhongPipeline() {}

void PhongPipeline::beginFrame(const xe::Vector4f &color) {
	m_device->beginFrame();
}

void PhongPipeline::endFrame() {
	m_device->endFrame();
}

void PhongPipeline::render(xe::sg::Light *light) {}

void PhongPipeline::render(xe::sg::Camera *camera) {
	assert(camera);

	m_view = camera->computeView();
	m_proj = camera->computeProj();

	this->updateMvp();
}

void PhongPipeline::render(xe::sg::Geometry *geometry) {}

void PhongPipeline::render(Mesh *mesh) {
	this->renderMesh(*mesh);
}

void PhongPipeline::updateMvp() {
	xe::Matrix4f mvp = this->getPVW();
	m_device->setUniformMatrix(m_program->getLocation("mvp"), 1, false, mvp.values);
}

void PhongPipeline::setWorldTransform(const xe::Matrix4f &world) {
	m_world = world;

	this->updateMvp();
}

xe::Matrix4f PhongPipeline::getPVW() const {
	return m_proj * m_view * m_world;
}

void PhongPipeline::renderMaterial(Material &material) {
	glEnable(GL_DEPTH_TEST);

    if (material.cullface) {
        glEnable(GL_CULL_FACE);

    } else {
        glDisable(GL_CULL_FACE);
    }

    GLuint textureId = 0;

    if (material.texture) {
        textureId = material.texture->getId();
    }
        
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    m_device->setUniform(m_program->getLocation("tex_diffuse"), 0);
    m_device->setUniform4(m_program->getLocation("mat_ambient"), 1, material.ambient.values);
    m_device->setUniform4(m_program->getLocation("mat_diffuse"), 1, material.diffuse.values);
    m_device->setUniform4(m_program->getLocation("mat_specular"), 1, material.specular.values);
    m_device->setUniform4(m_program->getLocation("mat_emissive"), 1, material.emissive.values);
    m_device->setUniform(m_program->getLocation("mat_shininess"), material.shininess);
}

void PhongPipeline::renderMesh(Mesh &mesh) {
	for (size_t mindex=0; mindex<mesh.materials.size(); mindex++) {
        Patch patch = mesh.patches[mindex];

        this->renderMaterial(mesh.materials[mindex]);

        m_device->render(mesh.subset.get(), mesh.primitive, patch.start, patch.count);
    }
}
