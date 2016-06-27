
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

PhongPipeline::PhongPipeline(xe::gfx::Device *device) {
	assert(device);

	m_device = device;

	// inicializar las matrices por defecto
	m_proj = xe::identity<float, 4>();
    m_view = xe::identity<float, 4>();
    m_world = xe::identity<float, 4>();

	// programa shader
	std::string vshader = loadTextFile("assets/shaders/vertex.glsl");
	std::string fshader = loadTextFile("assets/shaders/fragment.glsl");

	std::list<xe::gfx::ShaderSource> sources = {
		{xe::gfx::ShaderType::Vertex, vshader},
		{xe::gfx::ShaderType::Fragment, fshader}
	};

	m_program = m_device->createProgram(sources);

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

void PhongPipeline::render(xe::sg::Geometry *geometry) {
	
	if (auto *mesh = dynamic_cast<ModelPart*>(geometry)) {
		this->renderMesh(*mesh);
	}
}

void PhongPipeline::render(ModelPart *mesh) {
	this->renderMesh(*mesh);
}

void PhongPipeline::updateMvp() {
	xe::Matrix4f mvp = this->getPVW();

	int location = m_program->getLocation("mvp");

	m_device->setUniformMatrix(location, 1, false, mvp.values);
}

void PhongPipeline::setWorldTransform(const xe::Matrix4f &world) {
	m_world = world;

	this->updateMvp();
}

xe::Matrix4f PhongPipeline::getPVW() const {
	xe::Matrix4f mvp = m_proj * m_view * m_world;

	return mvp;
}

void PhongPipeline::renderMesh(ModelPart &part) {
	m_program->fillUniformLocations(part.materialFormat);

	for (size_t mindex=0; mindex<part.materials.size(); mindex++) {
        Patch patch = part.patches[mindex];

		m_device->setMaterial(&part.materials[mindex]);
		m_device->setMesh(part.mesh.get());
		m_device->render(part.primitive, patch.start, patch.count);
    }
}
