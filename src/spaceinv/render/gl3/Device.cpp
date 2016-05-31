
#include "Device.hpp"

namespace gl3 {
	void window_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	Device::Device() {
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
        
		glbinding::Binding::useCurrentContext();
		glbinding::Binding::initialize(true);

		assert(glGetError() == GL_NO_ERROR);

		glfwSetWindowSizeCallback(window, window_size_callback);

		std::cout << "Device inicializado correctamente." << std::endl;
	}

	Device::~Device() {
		::glfwDestroyWindow(window);
		::glfwTerminate();
	}

	void Device::pollEvents() {
		glfwPollEvents();
	}

	void Device::beginFrame() {
		auto clearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		glClear(clearFlags);

		assert(glGetError() == GL_NO_ERROR);
	}

	void Device::endFrame() {
		glFlush();
		glfwSwapBuffers(window);

		assert(glGetError() == GL_NO_ERROR);
	}

	int Device::getKey(int key) const {
		return ::glfwGetKey(window, key);
	}

	void Device::setProgram(const Program *program) {
		glUseProgram(program->getId());

		assert(glGetError() == GL_NO_ERROR);
	}

	void Device::setSubset(const Subset *subset) {
		glBindVertexArray(subset->getId());
	}

	void Device::render(const Subset *subset, GLenum primitive, std::size_t count) {
		glBindVertexArray(subset->getId());

		if (subset->indexed()) {
			//! TODO: Determinar tipo de datos de los indices a partir del formato
			glDrawElements(primitive, count, GL_UNSIGNED_INT, nullptr);

		} else {
			glDrawArrays(primitive, 0, count);
		}

		glBindVertexArray(0);

		assert(glGetError() == GL_NO_ERROR);
	}

	void Device::render(const Subset *subset, GLenum primitive, size_t start, size_t count) {
		glBindVertexArray(subset->getId());

		if (subset->indexed()) {
			glDrawElementsBaseVertex(primitive, count, GL_UNSIGNED_INT, nullptr, start);
		} else {
			glDrawArrays(primitive, start, count);
		}

		glBindVertexArray(0);

		assert(glGetError() == GL_NO_ERROR);
	}
}
