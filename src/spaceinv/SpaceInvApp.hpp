
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

#include "xe/gfx/Mesh.hpp"
#include "xe/gfx/Program.hpp"
#include "xe/gfx/Device.hpp"

#include "Entity.hpp"
#include "Scenario.hpp"
#include "Floor.hpp"
#include "render/TextureLoader.hpp"
#include "render/BdmModelLoader.hpp"
#include "render/PhongPipeline.hpp"
#include "render/LookAtCamera.hpp"
#include "render/BdmModel.hpp"
#include "render/BdmModelPart.hpp"

class SpaceInvApp {
public:
    SpaceInvApp();

    ~SpaceInvApp();

    bool running();
    
    void update(const float seconds);

    void render();
    
private:
    xe::gfx::DevicePtr m_device;
    xe::gfx::MeshFormat m_format;
    xe::gfx::UniformFormat m_materialFormat;

    PhongPipelinePtr m_pipeline;
    BdmModelLoader m_modelLoader;
    TextureLoader m_textureLoader;
    LookAtCamera m_camera;

    std::unique_ptr<Scenario> m_scenario;
    Entity m_player;

    xe::FileLocator m_locator;
    xe::sg::Scene m_scene;
    xe::sg::SceneRendererPtr m_renderer;

    xe::gfx::MeshPtr m_floorMesh;

    std::unique_ptr<Floor> m_floor;

    float m_angle = 0.0f;

private:
    void initCamera();
    
    void initScene();

    xe::gfx::MeshFormat createMeshFormat() const;

    xe::gfx::UniformFormat createMaterialFormat() const;

    void initGeometry();
};
