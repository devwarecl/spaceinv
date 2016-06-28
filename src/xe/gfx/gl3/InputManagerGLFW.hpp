
#pragma once

#ifndef __xe_gfx_inputmanagerglfw_hpp__
#define __xe_gfx_inputmanagerglfw_hpp__

#include <memory>
#include "xe/input/InputManager.hpp"
#include "xe/input/EventImpl.hpp"
#include "xe/gfx/gl3/OpenGL.hpp"

namespace xe { namespace gfx { namespace gl3 {

	class KeyboardGLFW : public xe::input::Keyboard {
	public:
		KeyboardGLFW() {}

		virtual ~KeyboardGLFW() {}

		virtual xe::input::KeyboardStatus* getStatus() override {
			return &status;
		}

		virtual const xe::input::KeyboardStatus* getStatus() const override {
			return &status;
		}

		virtual xe::input::Event<xe::input::KeyStroke>* getKeyStrokeEvent() override {
			return &keyStrokeEvent;
		}

		virtual void poll() override {}

		xe::input::KeyboardStatus status;
		xe::input::EventImpl<xe::input::KeyStroke> keyStrokeEvent;
	};

	class MouseGLFW : public xe::input::Mouse {
	public:
		virtual xe::input::MouseStatus getStatus() override {
			return status;
		}

		virtual void poll() override {}

		xe::input::MouseStatus status;
	};

	class InputManagerGLFW : public xe::input::InputManager {
	public:
		InputManagerGLFW();
		explicit InputManagerGLFW(GLFWwindow* window);

		virtual ~InputManagerGLFW() {}

		virtual KeyboardGLFW* getKeyboard() override {
			return &keyboard;
		}

		virtual MouseGLFW* getMouse() override {
			return &mouse;
		}

		void setWindow(GLFWwindow *window);

		GLFWwindow* getWindow() {
			return this->window;
		}

		const GLFWwindow* getWindow() const {
			return this->window;
		}

		virtual void poll() override;

	private:
		GLFWwindow *window = nullptr;
		KeyboardGLFW keyboard;
		MouseGLFW mouse;
	};
}}}

#endif 
