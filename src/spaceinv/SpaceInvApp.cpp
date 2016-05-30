
#include <vector>
#include <map>

#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
#include "xe/sg/Camera.hpp"

#include "gl3/Subset.hpp"
#include "gl3/Program.hpp"
#include "gl3/Device.hpp"

#include "Mesh.hpp"
#include "TextureLoader.hpp"
#include "MeshLoader.hpp"
#include "PhongPipeline.hpp"

class LookAtCamera : public xe::sg::Camera {
public:
	virtual ~LookAtCamera() {}

	virtual xe::Matrix4f computeView() const override {
		return xe::lookat(position, lookat, up);
	}

	virtual xe::Matrix4f computeProj() const override {
		return xe::perspective(fov, aspect, znear, zfar);
	}

	virtual xe::Rectf getViewport() const override {
		return xe::Rectf();
	}

public:
	xe::Vector3f position = {0.0f, 0.0f, 0.0f};
	xe::Vector3f lookat = {0.0f, 0.0f, 0.0f};
	xe::Vector3f up = {0.0f, 0.0f, 0.0f};

	float fov = xe::rad(60.0f);
	float aspect = 4.0f/3.0f;
	float znear = 0.0001f;;
	float zfar = 1000.0f;
};

class SpaceInvApp {
public:
    SpaceInvApp() {
		m_pipeline = std::make_unique<PhongPipeline>(&m_device);

        initGeometry();
        initCamera();
    }

    ~SpaceInvApp() {}

    bool running() {
        return m_device.getKey(GLFW_KEY_ESCAPE)==GLFW_RELEASE;
    }
    
    void update() {
        // animar modelo
        m_angle += 1.0f;
        
        // mover modelo
        auto translate = xe::translate<float>(m_position);
    }

    void render() {
		m_pipeline->beginFrame({0.0f, 0.0f, 0.0f, 1.0f});
		m_pipeline->render(&m_camera);
		m_pipeline->setWorldTransform(xe::rotatey(xe::rad(m_angle)));
		m_pipeline->render(&m_meshes[0]);
		m_pipeline->endFrame();
    }
    
private:
    gl3::Device m_device;
    gl3::SubsetFormat m_format;

	PhongPipelinePtr m_pipeline;
	MeshLoader m_meshLoader;
	TextureLoader m_textureLoader;
	LookAtCamera m_camera;

    std::vector<Mesh> m_meshes;
    xe::Vector3f m_position = {0.0f, 0.0f, 0.0f};
    float m_angle = 0.0f;
    
private:
    void initCamera() {
		m_camera.position = {0.0f, 2.5f, 7.5f};
		m_camera.lookat = {0.0f, 0.0f, 0.0f};
		m_camera.up = {0.0f, 1.0f, 0.0f};
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
