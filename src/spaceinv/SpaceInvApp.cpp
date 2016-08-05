
#include "SpaceInvApp.hpp"


#include <chrono>
#include "xe/gfx/gl3/DeviceGL.hpp"

SpaceInvApp::SpaceInvApp() {
    m_device = std::make_unique<xe::gfx::gl3::DeviceGL>();

    m_pipeline = std::make_unique<PhongPipeline>(m_device.get());
    m_renderer = std::make_unique<xe::sg::SceneRendererImpl>(m_pipeline.get());
    
    m_locator.addPath("assets/uprising/models/");
    m_locator.addPath("assets/uprising/bitmaps/");
    
    m_textureLoader.setLocator(&m_locator);
    m_textureLoader.setDevice(m_device.get());

    m_modelLoader.setLocator(&m_locator);
    m_modelLoader.setTextureLoader(&m_textureLoader);
    m_modelLoader.setDevice(m_device.get());

    initGeometry();
    initCamera();
    initScene();
}

SpaceInvApp::~SpaceInvApp() {}

bool SpaceInvApp::running() {
    auto status = m_device->getInputManager()->getKeyboard()->getStatus()->getKeyStatus(xe::input::KeyCode::KeyEsc);

    return status == xe::input::KeyStatus::Release;
}
    
void SpaceInvApp::update(const float seconds) {
    m_device->getInputManager()->poll();

    auto status = m_device->getInputManager()->getKeyboard()->getStatus();

    const float distance = 10.0f * seconds;
    
    if (status->isKeyPressed(xe::input::KeyCode::KeyLeft)) {
        m_player.step(-distance);
    }

    if (status->isKeyPressed(xe::input::KeyCode::KeyRight)) {
        m_player.step(distance);
    }

    if (status->isKeyPressed(xe::input::KeyCode::KeyUp)) {
        m_player.move(distance);
    }

    if (status->isKeyPressed(xe::input::KeyCode::KeyDown)) {
        m_player.move(-distance);
    }

    if (status->isKeyPushed(xe::input::KeyCode::KeySpace)) {
        m_player.fire();
    }

    m_scenario->update(seconds);
    m_player.syncNode();
}

void SpaceInvApp::render() {
    m_renderer->renderScene(&m_scene);
}
    
void SpaceInvApp::initCamera() {
    m_camera.position = {0.0f, 7.5f, -17.5f};
    m_camera.lookat = {0.0f, 0.5f, 0.0f};
    m_camera.up = {0.0f, 1.0f, 0.0f};
}
    
void SpaceInvApp::initScene() {

    // load all available models
    const char *models[] = {
        "iab1.bdm", "xspln.bdm", "alien.bdm", "himodA.bdm", "himodB.bdm", "iab1.bdm", "iab2.bdm", "iab3.bdm", "iab4.bdm", "iab5.bdm", 
        "iar1.bdm", "iav1.bdm", "iav2.bdm", "iav3.bdm", "iav4.bdm", "iav5.bdm", "ibb1.bdm", "ibb2.bdm", "ibb3.bdm", "ibb4.bdm", 
        "ibb5.bdm", "ibm1.bdm", "ibm2.bdm", "ibm3.bdm", "ibm4.bdm", "ibm5.bdm", "ibr1.bdm", "icy1t.bdm", "ien1p.bdm", "iib1.bdm", 
        "iib2.bdm", "iib3.bdm", "iib4.bdm", "iib5.bdm", "iir1.bdm", "iks1t.bdm", "iks2t.bdm", "iks3t.bdm", "ism1t.bdm", "ist1t.bdm", 
        "ist2t.bdm", "ist3t.bdm", "ist4t.bdm", "ist5t.bdm", "itb1.bdm", "itb2.bdm", "itb3.bdm", "itb4.bdm", "itb5.bdm", "itr1.bdm", 
        "itt1t.bdm", "pab1.bdm", "pab2.bdm", "pab3.bdm", "pab4.bdm", "pab5.bdm", "par1.bdm", "pat1.bdm", "pav1.bdm", "pav2.bdm", 
        "pav3.bdm", "pav4.bdm", "pav5.bdm", "pbb1.bdm", "pbb2.bdm", "pbb3.bdm", "pbb4.bdm", "pbb5.bdm", "pbm1.bdm", "pbm2.bdm", 
        "pbm3.bdm", "pbm4.bdm", "pbm5.bdm", "pbr1.bdm", "pcv1.bdm", "pcv2.bdm", "pcv3.bdm", "pcv4.bdm", "pcy1t.bdm", "pen1p.bdm", 
        "pib1.bdm", "pib2.bdm", "pib3.bdm", "pib4.bdm", "pib5.bdm", "pir1.bdm", "pks1t.bdm", "pks2t.bdm", "pks3t.bdm", "ppt1t.bdm", 
        "psm1t.bdm", "pst1t.bdm", "pst2t.bdm", "pst3t.bdm", "pst4t.bdm", "pst5t.bdm", "ptb1.bdm", "ptb2.bdm", "ptb3.bdm", "ptb4.bdm", 
        "ptb5.bdm", "ptr1.bdm", "ptt1t.bdm", "rab1.bdm", "rav1.bdm", "rbb1.bdm", "rbm1.bdm", "rht1t.bdm", "rib1.bdm", "rlt1t.bdm", 
        "rpw1.bdm", "rsm1t.bdm", "rst1t.bdm", "rtb1.bdm", "rtc1.bdm", "wan1.bdm", "wb11.bdm", "wbo1.bdm", "wcu1.bdm", "wcu2.bdm", 
        "wgp1.bdm", "wgp2.bdm", "wgt1.bdm", "whv1.bdm", "wig1.bdm", "wla1.bdm", "wlb1.bdm", "wls1.bdm", "wls2.bdm", "wls3.bdm", 
        "wls4.bdm", "wmb1.bdm", "wml1.bdm", "wmm1.bdm", "wmn1.bdm", "wms1.bdm", "wpu1.bdm", "wpu2.bdm", "wpu3.bdm", "wpu4.bdm", 
        "wpu5.bdm", "wr11.bdm", "wr21.bdm", "wr31.bdm", "wse1.bdm", "wsp1.bdm", "wsp2.bdm", "wSr1.bdm", "WT11.BDM", "wt12.bdm", 
        "wte1.bdm", "xcupd.bdm", "xflm.bdm", "xhealth.bdm", "xheat.bdm", "xhelx.bdm", "xhhiw.bdm", "xhsm.bdm", "xlasr.bdm", "xmbfg.bdm", 
        "xmine.bdm", "xmnly.bdm", "xmole.bdm", "xrack.bdm"
    };

    for (const char *name : models) {
        m_modelLoader.getModel(name, &m_materialFormat, &m_format);
    }

    // create the scene structure
    m_scene.rootNode.setRenderable(&m_camera);

    // create the scenario
    m_scenario = std::make_unique<Scenario>(&m_scene.rootNode, m_modelLoader.getModel("wls1.bdm"));

    // create the player
    xe::sg::SceneNode* playerNode = m_scene.rootNode.addChild()
        ->setRenderable(m_modelLoader.getModel("iav5.bdm"))
        ->setMatrix(xe::translate(xe::Vector3f(0.0f, 0.0f, 0.0f)))
    ;
    
    // auto playerNode = new xe::sg::SceneNode(m_modelLoader.getModel("iav5.bdm"), xe::translate(xe::Vector3f(0.0f, 0.0f, 0.0f)));

    m_player = Entity(m_scenario.get(), playerNode);

    // m_scene.rootNode.childs.emplace_back(playerNode);
}

xe::gfx::MeshFormat SpaceInvApp::createMeshFormat() const {
    xe::gfx::MeshFormat::AttribVector attribs = {
        {"v_coord", 3, xe::DataType::Float32, 0, xe::gfx::BufferType::Vertex},
        {"v_normal", 3, xe::DataType::Float32, 1, xe::gfx::BufferType::Vertex},
        {"v_texcoord", 2, xe::DataType::Float32, 2, xe::gfx::BufferType::Vertex}
    };

    return xe::gfx::MeshFormat(attribs);
}

xe::gfx::UniformFormat SpaceInvApp::createMaterialFormat() const {
    xe::gfx::UniformDescriptor descriptors[] = {
        {"mat_ambient", 4, xe::DataType::Float32},
        {"mat_diffuse", 4, xe::DataType::Float32},
        {"mat_specular", 4, xe::DataType::Float32},
        {"mat_emissive", 4, xe::DataType::Float32},
        {"mat_shininess", 1, xe::DataType::Float32},
        {"tex_diffuse", 1, xe::DataType::Int32}
    };

    xe::gfx::UniformFormat format;

    format.attribs.resize(6);

    std::copy(std::begin(descriptors), std::end(descriptors), std::begin(format.attribs));

    return format;
}

void SpaceInvApp::initGeometry() {
    m_format = this->createMeshFormat();
    m_materialFormat = this->createMaterialFormat();
}

int main() {
    SpaceInvApp app;
    
    while (app.running()) {
        static auto lastTime = std::chrono::high_resolution_clock::now();
        const auto current = std::chrono::high_resolution_clock::now();
    
        auto span = std::chrono::duration_cast<std::chrono::duration<float>>(current - lastTime);
        lastTime = std::chrono::high_resolution_clock::now();

        app.update(span.count());
        app.render();
    }

    return 0;
}
