
#include <vector>
#include <map>
#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
#include "xe/FileLocator.hpp"
#include "xe/sg/Camera.hpp"
#include "xe/sg/Scene.hpp"
#include "xe/sg/SceneRendererImpl.hpp"

#include "render/gl3/Subset.hpp"
#include "render/gl3/Program.hpp"
#include "render/gl3/Device.hpp"

#include "render/Mesh.hpp"
#include "render/TextureLoader.hpp"
#include "render/MeshLoader.hpp"
#include "render/PhongPipeline.hpp"
#include "render/LookAtCamera.hpp"

#include "Player.hpp"

class Model : public xe::sg::Renderable {
public:
	explicit Model(std::vector<Mesh> meshes) {
		m_meshes = std::move(meshes);
	}

	virtual void renderWith(xe::sg::Pipeline *pipeline) {
		this->renderWith(dynamic_cast<PhongPipeline*>(pipeline));
	}

	virtual void renderWith(PhongPipeline *pipeline) {
		assert(pipeline);
		assert(m_meshes.size() > 0);

		pipeline->render(&m_meshes[0]);
	}

private:
	std::vector<Mesh> m_meshes;
};

typedef std::unique_ptr<Model> ModelPtr;

class SpaceInvApp {
public:
    SpaceInvApp() {
		m_pipeline = std::make_unique<PhongPipeline>(&m_device);
		m_renderer = std::make_unique<xe::sg::SceneRendererImpl>(m_pipeline.get());
		
		m_locator.addPath("assets/uprising/");
		m_locator.addPath("assets/uprising/bitmaps/");
		
		m_textureLoader.setLocator(&m_locator);

		m_meshLoader.setLocator(&m_locator);
		m_meshLoader.setTextureLoader(&m_textureLoader);

        initGeometry();
        initCamera();
		initScene();
    }

    ~SpaceInvApp() {}

    bool running() {
        return m_device.getKey(GLFW_KEY_ESCAPE)==GLFW_RELEASE;
    }
    
    void update() {
		m_device.pollEvents();

		m_player.setTime(0.25f);

		if (m_device.getKey(GLFW_KEY_LEFT)) {
			m_camera.turn(0.025f);
		}

		if (m_device.getKey(GLFW_KEY_RIGHT)) {
			m_camera.turn(-0.025f);
		}

		if (m_device.getKey(GLFW_KEY_UP)) {
			m_camera.move(0.1f);
		}

		if (m_device.getKey(GLFW_KEY_DOWN)) {
			m_camera.move(-0.1f);
		}
    }

    void render() {
		m_renderer->renderScene(&m_scene);
    }
    
private:
    gl3::Device m_device;
    gl3::MeshFormat m_format;

	PhongPipelinePtr m_pipeline;
	MeshLoader m_meshLoader;
	TextureLoader m_textureLoader;
	LookAtCamera m_camera;

	Player m_player;

	xe::FileLocator m_locator;
	xe::sg::Scene m_scene;
	xe::sg::SceneRendererPtr m_renderer;

    float m_angle = 0.0f;

	std::map<std::string, ModelPtr> m_models;

	Model* getModel(const std::string &name) {
		Model* model = nullptr;

		auto modelIt = m_models.find(name);

		if (modelIt == std::end(m_models)) {
			m_models[name] = std::make_unique<Model>(m_meshLoader.createMeshSet(name, m_format));
			model = m_models[name].get();

		} else {
			model = modelIt->second.get();
		}

		return model;
	}

private:
    void initCamera() {
		m_camera.position = {0.0f, 0.5f, 12.5f};
		m_camera.lookat = {0.0f, 0.5f, 0.0f};
		m_camera.up = {0.0f, 1.0f, 0.0f};
    }
    
	void initScene() {
		auto playerNode = new xe::sg::SceneNode(this->getModel("models/iab1.bdm"), xe::translate(xe::Vector3f(0.0f, 0.0f, 0.0f)));

		xe::sg::SceneNode* models[] = {
			new xe::sg::SceneNode(this->getModel("models/ibb5.bdm"), xe::translate(xe::Vector3f(-5.0f, 0.0f, -5.0f))),
			new xe::sg::SceneNode(this->getModel("models/wsp1.bdm"), xe::translate(xe::Vector3f(0.0f, 0.0f, -5.0f))), 
			new xe::sg::SceneNode(this->getModel("models/wpu5.bdm"), xe::translate(xe::Vector3f(5.0f, 0.0f, -5.0f))), 
			new xe::sg::SceneNode(this->getModel("models/WT11.bdm"), xe::translate(xe::Vector3f(-5.0f, 0.0f, 5.0f))), 
			new xe::sg::SceneNode(this->getModel("models/rab1.bdm"), xe::translate(xe::Vector3f(0.0f, 0.0f, 5.0f))), 
			new xe::sg::SceneNode(this->getModel("models/wan1.bdm"), xe::translate(xe::Vector3f(5.0f, 0.0f, 5.0f)))
		};

		m_player = Player(playerNode);

		m_scene.rootNode.renderable = &m_camera;
		m_scene.rootNode.childs.emplace_back(playerNode);

		for (auto node : models) {
			m_scene.rootNode.childs.emplace_back(node);
		}
	}

	gl3::MeshFormat createMeshFormat() const {
		gl3::MeshFormat::AttribVector attribs = {
            gl3::MeshAttrib("v_coord", 3, xe::DataType::Float32, 0),
            gl3::MeshAttrib("v_normal", 3, xe::DataType::Float32, 1),
            gl3::MeshAttrib("v_texcoord", 2, xe::DataType::Float32, 2)
        };

        return gl3::MeshFormat(attribs);
	}

    void initGeometry() {
        m_format = this->createMeshFormat();
        
        assert(glGetError() == GL_NO_ERROR);
    }
};

int main() {
    SpaceInvApp app;

    while (app.running()) {
        app.update();
        app.render();
    }

    return 0;
}
