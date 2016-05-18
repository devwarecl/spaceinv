
#include <vector>
#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"

#include "gl3/Subset.hpp"
#include "gl3/Program.hpp"
#include "gl3/Device.hpp"

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

    void update() {
        m_angle += 1.0f;
        
        m_model = xe::rotatey(xe::rad(m_angle));
    }

    void render() {
        auto mvp = m_proj * m_view * m_model;
        
        m_device.beginFrame();
        m_device.setProgram(m_program.get());
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
    
    xe::Vector3f m_position;
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
            -1.0f, -1.0f, 0.0f
        };

        float normals[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };

        int indices[] = {
            0, 1, 2, 0, 2, 1
        };

        gl3::BufferVector buffers;
        buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, sizeof(vertices), vertices));
        buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, sizeof(normals), normals));
        
        auto ibuffer = std::make_unique<gl3::Buffer>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(indices), indices);

        gl3::SubsetFormat::AttribVector attribs = {
            gl3::SubsetAttrib("v_coord", 3, xe::DataType::Float32, 0),
            gl3::SubsetAttrib("v_normal", 3, xe::DataType::Float32, 1)
        };

        m_format = gl3::SubsetFormat(attribs);
        
        m_subset.reset(new gl3::Subset(m_format, std::move(buffers), std::move(ibuffer)));
        
        assert(glGetError() == GL_NO_ERROR);
    }
    
    void initShaders() {
        std::string vertexShader = R"(
#version 330

uniform mat4 mvp;

in vec3 v_coord;
in vec3 v_normal;

out vec3 f_normal;

vec3 transform(mat4 m, vec3 v, float w) {
    vec4 result = mvp * vec4(v_normal, w);
    return result.xyz;
}

void main() {
    gl_Position = mvp * vec4(v_coord, 1.0f);
    f_normal = (mvp * vec4(v_normal, 0.0f)).xyz;
}
        )";

        std::string fragmentShader = R"(
#version 330

in vec3 f_normal;
out vec4 color;

void main() {
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);   
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
