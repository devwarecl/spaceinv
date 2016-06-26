
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

#include "xe/gfx/gl3/MeshGL.hpp"
#include "xe/gfx/gl3/ProgramGL.hpp"
#include "xe/gfx/gl3/DeviceGL.hpp"

#include "ModelPart.hpp"
#include "render/TextureLoader.hpp"
#include "render/ModelLoader.hpp"
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
    xe::gfx::gl3::DeviceGL m_device;
    xe::gfx::MeshFormat m_format;
	xe::gfx::UniformFormat m_materialFormat;

	PhongPipelinePtr m_pipeline;
	ModelLoader m_modelLoader;
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

	xe::gfx::MeshFormat createMeshFormat() const;

	xe::gfx::UniformFormat createMaterialFormat() const;

    void initGeometry();
};
