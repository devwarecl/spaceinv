
#include <vector>
#include <map>
#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
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

class SpaceInvApp {
public:
    SpaceInvApp() {
		m_pipeline = std::make_unique<PhongPipeline>(&m_device);
		m_renderer = std::make_unique<xe::sg::SceneRendererImpl>(m_pipeline.get());
		
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
			m_player.moveLeft();
		}

		if (m_device.getKey(GLFW_KEY_RIGHT)) {
			m_player.moveRight();
		}

		if (m_device.getKey(GLFW_KEY_UP)) {
			m_player.moveForward();
		}

		if (m_device.getKey(GLFW_KEY_DOWN)) {
			m_player.moveBackward();
		}

		if (m_device.getKey(GLFW_KEY_SPACE)) {
			m_player.fire();
		}
    }

    void render() {
		m_renderer->renderScene(&m_scene);
    }
    
private:
    gl3::Device m_device;
    gl3::SubsetFormat m_format;

	PhongPipelinePtr m_pipeline;
	MeshLoader m_meshLoader;
	TextureLoader m_textureLoader;
	LookAtCamera m_camera;

	Player m_player;

	xe::sg::Scene m_scene;
	xe::sg::SceneRendererPtr m_renderer;

    std::vector<Mesh> m_meshes;
    float m_angle = 0.0f;
    
private:
    void initCamera() {
		m_camera.position = {0.0f, 2.5f, 7.5f};
		m_camera.lookat = {0.0f, 0.0f, 0.0f};
		m_camera.up = {0.0f, 1.0f, 0.0f};
    }
    
	void initScene() {
		m_scene.rootNode.renderable = &m_camera;
		m_scene.rootNode.childs.resize(1);
		m_scene.rootNode.childs[0].renderable = &m_meshes[0];

		m_player = Player(&m_scene.rootNode.childs[0]);
	}

    void initGeometry() {
        gl3::SubsetFormat::AttribVector attribs = {
            gl3::SubsetAttrib("v_coord", 3, xe::DataType::Float32, 0),
            gl3::SubsetAttrib("v_normal", 3, xe::DataType::Float32, 1),
            gl3::SubsetAttrib("v_texcoord", 2, xe::DataType::Float32, 2)
        };

        m_format = gl3::SubsetFormat(attribs);
        
        m_meshes = m_meshLoader.createMeshSet("assets/uprising/models/iab1.bdm", m_format);
        // m_meshes = createMeshSet("assets/uprising/models/ibb5.bdm", m_format);
        // m_meshes = createMeshSet("assets/uprising/models/wsp1.bdm", m_format);
        // m_meshes = createMeshSet("assets/uprising/models/wpu5.bdm", m_format);
        // m_meshes = createMeshSet("assets/uprising/models/WT11.bdm", m_format);
        // m_meshes = createMeshSet("assets/uprising/models/rab1.bdm", m_format);
        // m_meshes = createMeshSet("assets/uprising/models/wan1.bdm", m_format);

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
