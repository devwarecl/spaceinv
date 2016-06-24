
#pragma once

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
#include "Model.hpp"

class SpaceInvApp {
public:
    SpaceInvApp();

    ~SpaceInvApp();

    bool running();
    
    void update();

    void render();
    
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

private:
	Model* getModel(const std::string &name);

    void initCamera();
    
	void initScene();

	gl3::MeshFormat createMeshFormat() const;

    void initGeometry();
};
