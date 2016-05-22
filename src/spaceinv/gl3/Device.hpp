
#pragma once

#ifndef __gl3_device__
#define __gl3_device__

#include <cassert>
#include "GL.hpp"

namespace gl3 {
        
    void window_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

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
    
            window = ::glfwCreateWindow(1024, 768, "test", nullptr, nullptr);
    
            glfwMakeContextCurrent(window);
        
            glbinding::Binding::initialize(true);

            assert(glGetError() == GL_NO_ERROR);

    //#if defined(_DEBUG)
    //        glbinding::setCallbackMaskExcept(glbinding::CallbackMask::After, { "glGetError" });
    //
    //        glbinding::setAfterCallback([](const glbinding::FunctionCall &) {
    //            const auto error = glGetError();
    //
    //            if (error != GL_NO_ERROR) {
    //                std::cout << "error: " << std::hex << error << std::endl;
    //            }
    //        });
    //#endif

            glfwSetWindowSizeCallback(window, window_size_callback);

            std::cout << "Device inicializado correctamente." << std::endl;
        }

        ~Device() {
            ::glfwDestroyWindow(window);
            ::glfwTerminate();
        }

        void beginFrame() {
            glfwPollEvents();

            auto clearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

            glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
            glClear(clearFlags);

            assert(glGetError() == GL_NO_ERROR);
        }

        void endFrame() {
            glFlush();
            glfwSwapBuffers(window);

            assert(glGetError() == GL_NO_ERROR);
        }

        int getKey(int key) const {
            return ::glfwGetKey(window, GLFW_KEY_ESCAPE);
        }

        void setProgram(const Program *program) {
            glUseProgram(program->getId());

            assert(glGetError() == GL_NO_ERROR);
        }

        void render(const Subset *subset, GLenum primitive, std::size_t count) {
            glBindVertexArray(subset->getId());

            if (subset->indexed()) {
                //! TODO: Determinar tipo de datos de los indices a partir del formato de los indices
                glDrawElements(primitive, count, GL_UNSIGNED_INT, nullptr);

            } else {
                glDrawArrays(primitive, 0, count);
            }

            glBindVertexArray(0);

            assert(glGetError() == GL_NO_ERROR);
        }

        void setUniform(GLint location, float v) {
            glUniform1f(location, v);
        }

        void setUniform(GLint location, float v1, float v2) {
            glUniform2f(location, v1, v2);
        }

        void setUniform(GLint location, float v1, float v2, float v3) {
            glUniform3f(location, v1, v2, v3);
        }

        void setUniform(GLint location, float v1, float v2, float v3, float v4) {
            glUniform4f(location, v1, v2, v3, v4);
        }
        
        void setUniform(GLint location, int v) {
            glUniform1i(location, v);
        }

        void setUniform(GLint location, int v1, int v2) {
            glUniform2i(location, v1, v2);
        }

        void setUniform(GLint location, int v1, int v2, int v3) {
            glUniform3i(location, v1, v2, v3);
        }

        void setUniform(GLint location, int v1, int v2, int v3, int v4) {
            glUniform4i(location, v1, v2, v3, v4);
        }

        void setUniform1(GLint location, int total, const float *values) {
            glUniform1fv(location, total, values);
        }

        void setUniform2(GLint location, int total, const float *values) {
            glUniform2fv(location, total, values);
        }

        void setUniform3(GLint location, int total, const float *values) {
            glUniform3fv(location, total, values);
        }

        void setUniform4(GLint location, int total, const float *values) {
            glUniform4fv(location, total, values);
        }

        void setUniform1(GLint location, int total, const int *values) {
            glUniform1iv(location, total, values);
        }

        void setUniform2(GLint location, int total, const int *values) {
            glUniform2iv(location, total, values);
        }

        void setUniform3(GLint location, int total, const int *values) {
            glUniform3iv(location, total, values);
        }

        void setUniform4(GLint location, int total, const int *values) {
            glUniform4iv(location, total, values);
        }

        void setUniformMatrix(GLint location, int total, bool transpose, float *values) {
            glUniformMatrix4fv(location, total, transpose?GL_TRUE:GL_FALSE, values);
        }

    private:
        GLFWwindow *window = nullptr;
    };
}

#endif
