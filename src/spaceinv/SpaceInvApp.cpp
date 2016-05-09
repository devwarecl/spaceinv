
#define GLFW_INCLUDE_NONE

#include <glbinding/Binding.h>
#include <glbinding/gl33core/gl.h>
#include <GLFW/glfw3.h>

int main() {
    
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
    
    bool running = true;
    
    while(running) {
        glfwPollEvents();
        
        running = true;
        
        running = running && (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
        running = running && !glfwWindowShouldClose(window);
        
        auto clearFlags = gl33core::GL_COLOR_BUFFER_BIT | gl33core::GL_DEPTH_BUFFER_BIT;

        gl33core::glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
        gl33core::glClear(clearFlags);
        
        gl33core::glFlush();
        glfwSwapBuffers(window);
    }
    
    ::glfwDestroyWindow(window);
    ::glfwTerminate();
    
    return 0;
}
