
#include <vector>
#include <cassert>

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"

#include "gl3/Subset.hpp"
#include "gl3/Program.hpp"
#include "gl3/Device.hpp"

struct Assets {
    gl3::SubsetFormat format;
    gl3::Subset subset;

    gl3::Program program;
    
    void initGeometry() {
        float vertices[] =  {
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
        };

        float normals[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };

        int indices[] = {
            0, 1, 2, 0, 2, 1
        };

        std::vector<gl3::Buffer> buffers = {
            std::move(gl3::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, sizeof(vertices), vertices)),
            std::move(gl3::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, sizeof(normals), normals)),
        };

        gl3::Buffer ibuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(indices), indices);

        gl3::SubsetFormat::AttribVector attribs = {
            gl3::SubsetAttrib("v_coord", 3, xe::DataType::Float32, 0),
            gl3::SubsetAttrib("v_normal", 3, xe::DataType::Float32, 1)
        };

        format = gl3::SubsetFormat(attribs);
        subset = gl3::Subset(format, std::move(buffers), std::move(ibuffer));

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

        gl3::Program::ShaderVector shaders = {
            gl3::Shader(GL_VERTEX_SHADER, vertexShader),
            gl3::Shader(GL_FRAGMENT_SHADER, fragmentShader)
        };

        program = gl3::Program(std::move(shaders));

        assert(glGetError() == GL_NO_ERROR);
    }

    Assets() {
        initGeometry();
        initShaders();
    }

    ~Assets () {}
};

class SpaceInvApp {
public:
    SpaceInvApp() {}

    ~SpaceInvApp() {}

    bool running() {
        return device.getKey(GLFW_KEY_ESCAPE)==GLFW_RELEASE;
    }

    void update() {}

    void render() {
        float matrix[] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        
        device.beginFrame();
        device.setProgram(assets.program);
        device.setUniformMatrix(assets.program.getLocation("mvp"), 1, false, matrix);
        device.render(assets.subset, GL_TRIANGLES, 6);
        device.endFrame();

        assert(glGetError() == GL_NO_ERROR);
    }

private:
    gl3::Device device;
    Assets assets;
};

int main() {
    SpaceInvApp app;

    while (app.running()) {
        app.update();
        app.render();
    }

    return 0;
}
