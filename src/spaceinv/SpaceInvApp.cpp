
#include <vector>
#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"

#include "gl3/Subset.hpp"
#include "gl3/Program.hpp"
#include "gl3/Device.hpp"

struct Material {
    bool cullFace = true;

    xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
    xe::Vector4f diffuse = {0.8f, 0.8f, 0.8f, 1.0f};
    xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
    xe::Vector4f emissive = {0.0f, 0.0f, 0.0f, 1.0f};

    float shininess = 0.0f;
};

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
        if (material.cullFace) {
            glEnable(GL_CULL_FACE);

        } else {
            glDisable(GL_CULL_FACE);
        }

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
        xe::Vector3f displace = {0.0f, 0.0f, 0.0f};
        
        if (m_device.getKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
            displace.x = 1.0f;
        }
        
        if (m_device.getKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
            displace.x = -1.0f;
        }
        
        m_position += displace;
        auto translate = xe::translate<float>(m_position);
        
        m_model = rotate * translate;
    }

    void render() {
        auto mvp = m_proj * m_view * m_model;
        
        m_device.beginFrame();
        m_device.setProgram(m_program.get());
        
        renderMaterial(m_material);
        
        m_device.setUniformMatrix(m_program->getLocation("mvp"), 1, false, mvp.values);
        m_device.render(m_subset.get(), GL_TRIANGLES, 6);
        m_device.endFrame();
        
        assert(glGetError() == GL_NO_ERROR);
    }
    
private:
    gl3::Device m_device;
    gl3::SubsetFormat m_format;
    gl3::SubsetPtr m_subset;
    gl3::ProgramPtr m_program;
    
    xe::Matrix4f m_proj;
    xe::Matrix4f m_view;
    xe::Matrix4f m_model;
    
    Material m_material;
    
    xe::Vector3f m_position = {0.0f, 0.0f, 0.0f};
    float m_angle = 0.0f;
    
private:
    void initMatrices() {
        m_proj = xe::perspective(xe::rad(60.0f), 4.0f/3.0f, 0.01f, 1000.0f);
        m_view = xe::lookat<float>({0.0f, 2.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
        m_model = xe::identity<float, 4>();
    }
    
    void initGeometry() {
        float vertices[] =  {
            0.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            
            0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };

        float normals[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f
        };

        gl3::BufferVector buffers;
        buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, sizeof(vertices), vertices));
        buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, sizeof(normals), normals));

        gl3::SubsetFormat::AttribVector attribs = {
            gl3::SubsetAttrib("v_coord", 3, xe::DataType::Float32, 0),
            gl3::SubsetAttrib("v_normal", 3, xe::DataType::Float32, 1)
        };

        m_format = gl3::SubsetFormat(attribs);
        
        m_subset.reset(new gl3::Subset(m_format, std::move(buffers)));
        
        assert(glGetError() == GL_NO_ERROR);
    }
    
    void initShaders() {
        std::string vertexShader = R"(
#version 330

uniform mat4 mvp;

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform vec4 mat_emissive;
uniform float mat_shininess;

in vec3 v_coord;
in vec3 v_normal;

out vec3 f_normal;

vec3 transform(mat4 m, vec3 v, float w) {
    vec4 result = mvp * vec4(v_normal, w);
    return result.xyz;
}

void main() {
    gl_Position = mvp * vec4(v_coord, 1.0f);
    f_normal = normalize((mvp * vec4(v_normal, 0.0f)).xyz);
}
        )";

        std::string fragmentShader = R"(
#version 330

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform vec4 mat_emissive;
uniform float mat_shininess;

in vec3 f_normal;
out vec4 p_color;

void main() {
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec3 light_dir = normalize(vec3(0.0f, 0.0f, 1.0f));
    float light_factor = max(dot(f_normal, light_dir), 0.0f);
    
    color += mat_ambient + mat_emissive;
    
    if (light_factor > 0.0) {
        // diffuse
        color += mat_diffuse * light_factor;
        
        // specular
        vec3 light_dir_half = normalize(light_dir + vec3(0.0f, 0.0f, 1.0f));
        float light_factor_specular = max(dot(f_normal, light_dir_half), 0.0f);
        
        color += mat_specular * pow(light_factor_specular, mat_shininess);
    }
    
    p_color = color;
}
        )";
        
        auto shader1 = std::make_unique<gl3::Shader>(GL_VERTEX_SHADER, vertexShader);
        auto shader2 = std::make_unique<gl3::Shader>(GL_FRAGMENT_SHADER, fragmentShader);

        gl3::ShaderVector shaders;
        shaders.push_back(std::move(shader1));
        shaders.push_back(std::move(shader2));
        
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
