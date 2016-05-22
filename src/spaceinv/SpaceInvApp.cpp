
#include <vector>
#include <cassert>

#include "FreeImage.h"

#include "bdm/BdmFile.hpp"

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"

#include "gl3/Subset.hpp"
#include "gl3/Program.hpp"
#include "gl3/Device.hpp"
#include "gl3/Texture.hpp"

class TextureLoader {
public:
    TextureLoader() {
        ::FreeImage_Initialise();
    }

    ~TextureLoader() {
        ::FreeImage_DeInitialise();
    }

    void addPath(const std::string &path) {
        m_paths.push_back(path);
    }

    gl3::TexturePtr loadTexture(const std::string &file) {
        gl3::TexturePtr texture;

        if (m_paths.size()) {
            for (const auto &path : m_paths) {
                texture = this->doLoadTexture(path + file);

                if (texture) {
                    break;
                }
            }
        } else {
            texture = this->doLoadTexture(file);
        }

        return texture;
    }

protected:
    gl3::TexturePtr doLoadTexture(const std::string &file) {
        FIBITMAP *bitmap = ::FreeImage_Load(FIF_BMP, file.c_str());

        // bitmap = FreeImage_ConvertTo24Bits(bitmap);

        auto width = ::FreeImage_GetWidth(bitmap);
        auto height = ::FreeImage_GetHeight(bitmap);
        auto bpp = ::FreeImage_GetBPP(bitmap);
        void* data = ::FreeImage_GetBits(bitmap);
        
        auto texture = std::make_unique<gl3::Texture>(width, height, data);

        ::FreeImage_Unload(bitmap);

        return texture;
    }

private:
    std::list<std::string> m_paths;
};

struct Box {
    xe::Vector3f pmin;
    xe::Vector3f pmax;

    xe::Vector3f size() const {
        return pmax - pmin;
    }

    xe::Vector3f center() const {
        return pmin + size() * 0.5f;
    }
};

struct Material {
    bool cullface = true;

    xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
    xe::Vector4f diffuse = {0.8f, 0.8f, 0.8f, 1.0f};
    xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
    xe::Vector4f emissive = {0.0f, 0.0f, 0.0f, 1.0f};

    float shininess = 0.0f;

    gl3::TexturePtr texture;
};

struct Model {
    gl3::SubsetFormat format;
    gl3::SubsetPtr subset;
    size_t count = 0;
    Material material;
    GLenum primitive = GL_TRIANGLES;
};

Model loadModelBDM(const std::string &path, const gl3::SubsetFormat &format) {
    bdm::BdmFile bdmFile(path.c_str());

    auto &model_vertices = bdmFile.vertices();
    auto &model_faces = bdmFile.faces();

    std::vector<xe::Vector3f> vertices;
    std::vector<xe::Vector3f> normals;
    std::vector<xe::Vector2f> texcoords;

    // duplicar vertices
    for (auto &face : model_faces) {
        for (auto index : face.values) {
            auto vertex = xe::Vector3f(model_vertices[index].values);
            vertices.push_back(vertex);
        }
    }

    // generar caja de escalado
    Box scaleBox;

    for (size_t i=0; i<vertices.size(); i++) {
        if (i==0) {
            scaleBox.pmin = vertices[0];
            scaleBox.pmax = vertices[0];
        }

        scaleBox.pmin = xe::minimize(scaleBox.pmin, vertices[i]);
        scaleBox.pmax = xe::maximize(scaleBox.pmax, vertices[i]);
    }

    auto center = scaleBox.center();
    auto length = xe::max(scaleBox.size());

    // post procesar modelo
    for (size_t i=0; i<vertices.size(); i+=3) {

        // escalar modelo
        for (int j=0; j<3; j++) {
            vertices[i + j] -= center;
            vertices[i + j] *= 10.0f/length;
        }

        // generar normales
        auto v1 = vertices[i + 1] - vertices[i + 0];
        auto v2 = vertices[i + 2] - vertices[i + 0];

        auto n = xe::normalize(xe::cross(v2, v1));

        for (int j=0; j<3; j++) {
            normals.push_back(n);
        }
    }

    // finalizar construccion modelo
    Model model;

    // cargar texturas 
    // TODO: Considerar el resto de las texturas
    xe::Vector2f texcoordscale = {1.0f, 1.0f};

    TextureLoader loader;

    loader.addPath("assets/bitmaps/");

    for (const std::string &file : bdmFile.textures()) {
        if (file != "") {
            model.material.texture = loader.loadTexture(file);

            if (model.material.texture) {

                texcoordscale = xe::Vector2f (
                    1.0f/model.material.texture->getWidth(),
                    1.0f/model.material.texture->getHeight()
                );
            }

            break;
        }
    }

    // copiar los datos de coordenadas de textura
    for (auto &t : bdmFile.texcoords()) {
        xe::Vector2f texcoord = xe::Vector2f(t.values) * texcoordscale;

        std::cout << texcoord << std::endl;

        texcoords.push_back(texcoord);
    }

    // cargar datos a OpenGL
    gl3::BufferVector buffers;
    buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices));
    buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, normals));
    buffers.emplace_back(new gl3::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, texcoords));
    
    model.count = vertices.size();
    model.primitive = GL_TRIANGLES;
    model.subset = std::make_unique<gl3::Subset>(format, std::move(buffers));
    model.format = format;

    return model;
}

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
        
        renderMaterial(m_model.material);
        
        m_device.setUniformMatrix(m_program->getLocation("mvp"), 1, false, mvp.values);
        m_device.render(m_model.subset.get(), m_model.primitive, m_model.count);
        m_device.endFrame();
        
        assert(glGetError() == GL_NO_ERROR);
    }
    
private:
    gl3::Device m_device;
    gl3::SubsetFormat m_format;
    gl3::ProgramPtr m_program;
    
    Model m_model;

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
        
        m_model = loadModelBDM("assets/models/wls1.bdm", m_format);
        
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
in vec2 v_texcoord;

out vec3 f_normal;
out vec2 f_texcoord;

vec3 transform(mat4 m, vec3 v, float w) {
    vec4 result = mvp * vec4(v_normal, w);
    return result.xyz;
}

void main() {
    gl_Position = mvp * vec4(v_coord, 1.0f);
    f_normal = normalize((mvp * vec4(v_normal, 0.0f)).xyz);
    f_texcoord = v_texcoord;
}
        )";

        std::string fragmentShader = R"(
#version 330

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform vec4 mat_emissive;
uniform float mat_shininess;

uniform sampler2D tex_diffuse;

in vec3 f_normal;
in vec2 f_texcoord;

out vec4 p_color;

void main() {
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec3 light_dir = normalize(vec3(0.0f, 0.0f, 1.0f));
    float light_factor = max(dot(f_normal, light_dir), 0.0f);
    
    // ambient y emissive
    color += mat_ambient + mat_emissive;

    if (light_factor > 0.0) {
        // diffuse
        // color += (mat_diffuse*0.5f + texture(tex_diffuse, f_texcoord)*0.5f) * light_factor;
        // color += mat_diffuse * texture(tex_diffuse, f_texcoord) * light_factor;
        color += texture(tex_diffuse, f_texcoord) * light_factor + mat_diffuse*0.0f;        
        
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
