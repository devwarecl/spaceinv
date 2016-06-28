

#include "InputManagerGLFW.hpp"
#include "xe/gfx/gl3/DeviceGL.hpp"

namespace xe { namespace gfx { namespace gl3 {

	void xe_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_REPEAT) {
            return;
        }
        
		auto driver = static_cast<xe::gfx::gl3::DeviceGL*>(::glfwGetWindowUserPointer(window));
		auto manager = static_cast<InputManagerGLFW*>(driver->getInputManager());

		// determine key code
		auto code = xe::input::KeyCode::Unknown;

        switch (key) {
            case GLFW_KEY_ESCAPE:	code = xe::input::KeyCode::KeyEsc;		break;
            case GLFW_KEY_LEFT:		code = xe::input::KeyCode::KeyLeft;	break;
            case GLFW_KEY_RIGHT:	code = xe::input::KeyCode::KeyRight;	break;
            case GLFW_KEY_UP:		code = xe::input::KeyCode::KeyUp;		break;
            case GLFW_KEY_DOWN:		code = xe::input::KeyCode::KeyDown;	break;
            case GLFW_KEY_ENTER:	code = xe::input::KeyCode::KeyEnter;	break;
        }

		// determine key status
        auto status = xe::input::KeyStatus::Unknown;
		
		switch (action) {
            case GLFW_RELEASE:  status = xe::input::KeyStatus::Release;    break;
            case GLFW_PRESS:    status = xe::input::KeyStatus::Press;      break;
		}
		
		// set the key status
		manager->getKeyboard()->getStatus()->setKeyStatus(code, status);
		
		/*
		else if (action == GLFW_REPEAT) {
			xe::input::KeyStroke keyStroke;
			keyStroke.code = code;
			keyStroke.status = status;

			manager->getKeyboard()->getKeyStrokeEvent()->raise(keyStroke);
		}
		*/
	}

	InputManagerGLFW::InputManagerGLFW() {}

	InputManagerGLFW::InputManagerGLFW(GLFWwindow* window) {
		this->setWindow(window);
	}

	void InputManagerGLFW::poll() {
		::glfwPollEvents();
	}

	void InputManagerGLFW::setWindow(GLFWwindow *window) {
		::glfwSetKeyCallback(window, xe_handle_key);
		this->window = window;
	}
}}}
