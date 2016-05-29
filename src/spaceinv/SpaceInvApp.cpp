
#include <vector>
#include <map>
#include <fstream>
#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"

#include "gl3/Subset.hpp"
#include "gl3/Program.hpp"
#include "gl3/Device.hpp"

#include "Mesh.hpp"
#include "TextureLoader.hpp"
#include "MeshLoader.hpp"

class SpaceInvApp {
public:
    SpaceInvApp() {
        initGeometry();
        initShaders();
        initMatrices();
    }

    ~SpaceInvApp() {}

    bool running() {
        return m_device.getKey(GLFW_KEY_ESCAPE)==GLFW_RELEASE;
    }
    
    void renderMaterial(const Material &material) {
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

        m_device.setUniform(m_program->getLocation("tex_diffuse"), 0);
        m_device.setUniform4(m_program->getLocation("mat_ambient"), 1, material.ambient.values);
        m_device.setUniform4(m_program->getLocation("mat_diffuse"), 1, material.diffuse.values);
        m_device.setUniform4(m_program->getLocation("mat_specular"), 1, material.specular.values);
        m_device.setUniform4(m_program->getLocation("mat_emissive"), 1, material.emissive.values);
        m_device.setUniform(m_program->getLocation("mat_shininess"), material.shininess);
    }
    
    void update() {
        // animar modelo
        m_angle += 1.0f;
        
        auto rotate = xe::rotatey(xe::rad(m_angle));
        
        // mover modelo
        auto translate = xe::translate<float>(m_position);
        
        m_world = rotate * translate;
    }

    void render() {
        auto mvp = m_proj * m_view * m_world;
        
        m_device.beginFrame();
        m_device.setProgram(m_program.get());
        
        auto &mesh = m_meshes[0];

        m_device.setUniformMatrix(m_program->getLocation("mvp"), 1, false, mvp.values);

        for (size_t mindex=0; mindex<mesh.materials.size(); mindex++) {

            Patch patch = mesh.patches[mindex];

            this->renderMaterial(mesh.materials[mindex]);

            m_device.render(mesh.subset.get(), mesh.primitive, patch.start, patch.count);
        }

        m_device.endFrame();
        
        assert(glGetError() == GL_NO_ERROR);
    }
    
private:
    gl3::Device m_device;
    gl3::SubsetFormat m_format;
    gl3::ProgramPtr m_program;

	MeshLoader m_meshLoader;
	TextureLoader m_textureLoader;

    std::vector<Mesh> m_meshes;

    xe::Matrix4f m_proj;
    xe::Matrix4f m_view;
    xe::Matrix4f m_world;
    
    xe::Vector3f m_position = {0.0f, 0.0f, 0.0f};
    float m_angle = 0.0f;
    
private:
    void initMatrices() {
        m_proj = xe::perspective(xe::rad(60.0f), 4.0f/3.0f, 0.01f, 10000.0f);
        m_view = xe::lookat<float>({0.0f, 2.5f, 7.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
        m_world = xe::identity<float, 4>();
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

    void initShaders() {
        std::string vertexShader = this->loadTextFile("assets/shaders/vertex.glsl");
        std::string fragmentShader = this->loadTextFile("assets/shaders/fragment.glsl");

        gl3::ShaderVector shaders;
        shaders.emplace_back(new gl3::Shader (GL_VERTEX_SHADER, vertexShader));
        shaders.emplace_back(new gl3::Shader (GL_FRAGMENT_SHADER, fragmentShader));

        m_program = std::make_unique<gl3::Program>(std::move(shaders));
        
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
