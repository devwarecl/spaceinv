
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

#include "render/gl3/MeshGL.hpp"
#include "render/gl3/ProgramGL.hpp"
#include "render/gl3/DeviceGL.hpp"

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
		
		m_locator.addPath("assets/uprising/models/");
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
    gl3::DeviceGL m_device;
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
		m_camera.position = {0.0f, 5.5f, 12.5f};
		m_camera.lookat = {0.0f, 0.5f, 0.0f};
		m_camera.up = {0.0f, 1.0f, 0.0f};
    }
    
	void initScene() {
		auto playerNode = new xe::sg::SceneNode(this->getModel("iab1.bdm"), xe::translate(xe::Vector3f(0.0f, 0.0f, 0.0f)));

		const char *models[] = {
			"xspln.bdm", "alien.bdm", "himodA.bdm", "himodB.bdm", "iab1.bdm", "iab2.bdm", "iab3.bdm", "iab4.bdm", "iab5.bdm", "iar1.bdm", "iav1.bdm", "iav2.bdm", "iav3.bdm", "iav4.bdm", "iav5.bdm", "ibb1.bdm", "ibb2.bdm", "ibb3.bdm", "ibb4.bdm", "ibb5.bdm", "ibm1.bdm", "ibm2.bdm", "ibm3.bdm", "ibm4.bdm", "ibm5.bdm", "ibr1.bdm", "icy1t.bdm", "ien1p.bdm", "iib1.bdm", "iib2.bdm", "iib3.bdm", "iib4.bdm", "iib5.bdm", "iir1.bdm", "iks1t.bdm", "iks2t.bdm", "iks3t.bdm", "ism1t.bdm", "ist1t.bdm", "ist2t.bdm", "ist3t.bdm", "ist4t.bdm", "ist5t.bdm", "itb1.bdm", "itb2.bdm", "itb3.bdm", "itb4.bdm", "itb5.bdm", "itr1.bdm", "itt1t.bdm", "pab1.bdm", "pab2.bdm", "pab3.bdm", "pab4.bdm", "pab5.bdm", "par1.bdm", "pat1.bdm", "pav1.bdm", "pav2.bdm", "pav3.bdm", "pav4.bdm", "pav5.bdm", "pbb1.bdm", "pbb2.bdm", "pbb3.bdm", "pbb4.bdm", "pbb5.bdm", "pbm1.bdm", "pbm2.bdm", "pbm3.bdm", "pbm4.bdm", "pbm5.bdm", "pbr1.bdm", "pcv1.bdm", "pcv2.bdm", "pcv3.bdm", "pcv4.bdm", "pcy1t.bdm", "pen1p.bdm", "pib1.bdm", "pib2.bdm", "pib3.bdm", "pib4.bdm", "pib5.bdm", "pir1.bdm", "pks1t.bdm", "pks2t.bdm", "pks3t.bdm", "ppt1t.bdm", "psm1t.bdm", "pst1t.bdm", "pst2t.bdm", "pst3t.bdm", "pst4t.bdm", "pst5t.bdm", "ptb1.bdm", "ptb2.bdm", "ptb3.bdm", "ptb4.bdm", "ptb5.bdm", "ptr1.bdm", "ptt1t.bdm", "rab1.bdm", "rav1.bdm", "rbb1.bdm", "rbm1.bdm", "rht1t.bdm", "rib1.bdm", "rlt1t.bdm", "rpw1.bdm", "rsm1t.bdm", "rst1t.bdm", "rtb1.bdm", "rtc1.bdm", "wan1.bdm", "wb11.bdm", "wbo1.bdm", "wcu1.bdm", "wcu2.bdm", "wgp1.bdm", "wgp2.bdm", "wgt1.bdm", "whv1.bdm", "wig1.bdm", "wla1.bdm", "wlb1.bdm", "wls1.bdm", "wls2.bdm", "wls3.bdm", "wls4.bdm", "wmb1.bdm", "wml1.bdm", "wmm1.bdm", "wmn1.bdm", "wms1.bdm", "wpu1.bdm", "wpu2.bdm", "wpu3.bdm", "wpu4.bdm", "wpu5.bdm", "wr11.bdm", "wr21.bdm", "wr31.bdm", "wse1.bdm", "wsp1.bdm", "wsp2.bdm", "wSr1.bdm", "WT11.BDM", "wt12.bdm", "wte1.bdm", "xcupd.bdm", "xflm.bdm", "xhealth.bdm", "xheat.bdm", "xhelx.bdm", "xhhiw.bdm", "xhsm.bdm", "xlasr.bdm", "xmbfg.bdm", "xmine.bdm", "xmnly.bdm", "xmole.bdm", "xrack.bdm"
		};

		std::list<xe::sg::SceneNode*> nodes;

		const int count_per_width = 10;
		int current = 0;

		float diff = 5.0f;
		float x = -diff * float(count_per_width / 2);
		float z = x;

		for (const char *model : models) {
			nodes.push_back(new xe::sg::SceneNode(this->getModel(model), xe::translate(xe::Vector3f(x, 0.0f, z))));

			if (++current % count_per_width == 0) {
				x = -diff * float(count_per_width / 2);
				z += diff;

			} else {
				x += diff;
			}
		}

		m_player = Player(&m_scene.rootNode, playerNode);

		m_scene.rootNode.renderable = &m_camera;
		m_scene.rootNode.childs.emplace_back(playerNode);

		for (auto node : nodes) {
			m_scene.rootNode.childs.emplace_back(node);
		}
	}

	gl3::MeshFormat createMeshFormat() const {
		gl3::MeshFormat::AttribVector attribs = {
			{"v_coord", 3, xe::DataType::Float32, 0},
			{"v_normal", 3, xe::DataType::Float32, 1},
			{"v_texcoord", 2, xe::DataType::Float32, 2}
        };

        return gl3::MeshFormat(attribs);
	}

    void initGeometry() {
        m_format = this->createMeshFormat();
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
