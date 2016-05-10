
#define GLFW_INCLUDE_NONE

#pragma warning (disable:4251)

#include <glbinding/Binding.h>
#include <glbinding/gl33core/gl.h>
#include <GLFW/glfw3.h>
#include <cassert>

class Buffer {
public:
    Buffer() {}

    Buffer(gl33core::GLenum target_, std::size_t size_, gl33core::GLenum usage) {
        size = size_;
        target = target_;

        gl33core::glGenBuffers(1, &id);
        gl33core::glBindBuffer(target, id);
        gl33core::glBufferData(target, size, nullptr, usage);
    }

    ~Buffer() {
        gl33core::glDeleteBuffers(1, &id);
    }

    void write(const void* data) {
        gl33core::glBufferSubData(target, 0, size, data);
    }

    void read(void *data) const {
        gl33core::glGetBufferSubData(target, 0, size, data);
    }

    gl33core::GLint getId() const {
        return id;
    }

    gl33core::GLenum getTarget() const {
        return target;
    }

private:
    gl33core::GLenum target;
    gl33core::GLuint id = 0;
    std::size_t size = 0;
};

struct SubsetAttrib {

};

class Subset {
public:
    template<typename BufferContainer>
    explicit Subset(const BufferContainer &buffers, const Buffer &ibuffer) {
        gl33core::glGenVertexArrays(1, &id);
        gl33core::glBindVertexArray(id);

        for (const Buffer &buffer : buffers) {
            
        }

        gl33core::glBindVertexArray(0);
    }

    ~Subset() {
        gl33core::glDeleteVertexArrays(1, &id);
    }

    gl33core::GLuint getId() const {
        return id;
    }

private:
    gl33core::GLuint id = 0;
};

class Shader {
public:
    Shader() {}

    Shader(gl33core::GLenum type_, const std::string &glsl) {
        type = type_;
        id = gl33core::glCreateShader(type);

        auto source = static_cast<const gl33core::GLchar *const>(glsl.c_str());
        auto size = static_cast<gl33core::GLsizei>(glsl.size());
        gl33core::glShaderSource (id, 1, &source, &size);
        gl33core::glCompileShader(id);
    }

    ~Shader() {
        gl33core::glDeleteShader(id);
    }

    gl33core::GLenum getType() const {
        return type;
    }

    gl33core::GLuint getId() const {
        return id;
    }

private:
    gl33core::GLenum type;
    gl33core::GLuint id = 0;
};

class Program {
public:
    Program() {}

    template<typename ShaderContainer>
    Program(const ShaderContainer &shaders) {
        id = gl33core::glCreateProgram();

        for (const Shader &shader : shaders) {
            gl33core::glAttachShader(id, shader.getId());
        }

        gl33core::glLinkProgram(id);
    }

    gl33core::GLuint getId() const {
        return id;
    }

    ~Program() {
        gl33core::glDeleteProgram(id);
    }

private:
    gl33core::GLuint id = 0;
};

class Device {
public:
    Device() {
        ::glfwInit();
    
        int hints[][2] = {
            // version
            {GLFW_CONTEXT_VERSION_MAJOR, 3},
            {GLFW_CONTEXT_VERSION_MINOR, 3},
            {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
        
            // framebuffer
            {GLFW_RED_BITS, 8},
            {GLFW_GREEN_BITS, 8},
            {GLFW_BLUE_BITS, 8},
            {GLFW_ALPHA_BITS, 8} ,
            {GLFW_DEPTH_BITS,  24},
            {GLFW_STENCIL_BITS, 8}
        };
    
        for (auto hint : hints) {
            ::glfwWindowHint(hint[0], hint[1]);
        }
    
        GLFWwindow *window = ::glfwCreateWindow(640, 480, "test", nullptr, nullptr);
    
        glfwMakeContextCurrent(window);
    
        glbinding::Binding::initialize(false);
    }

    ~Device() {
        ::glfwDestroyWindow(window);
        ::glfwTerminate();
    }

    void beginFrame() {
        glfwPollEvents();

        auto clearFlags = gl33core::GL_COLOR_BUFFER_BIT | gl33core::GL_DEPTH_BUFFER_BIT;

        gl33core::glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
        gl33core::glClear(clearFlags);
    }

    void endFrame() {
        gl33core::glFlush();
        glfwSwapBuffers(window);
    }

    int getKey(int key) const {
        return ::glfwGetKey(window, GLFW_KEY_ESCAPE);
    }

private:
    GLFWwindow *window = nullptr;
};

class SpaceInvApp {
public:

    SpaceInvApp() {}

    ~SpaceInvApp() {}

private:
    Device device;
    Program program;
    Shader vshader;
    Shader fshader;
};

int main() {    
    Device device;

    bool running = true;
    
    while(running) {
        running = device.getKey(GLFW_KEY_ESCAPE)==GLFW_RELEASE;

        device.beginFrame();

        device.endFrame();
    }
    
    return 0;
}
