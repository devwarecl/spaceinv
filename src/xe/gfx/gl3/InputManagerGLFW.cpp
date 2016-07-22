

#include "InputManagerGLFW.hpp"
#include "xe/gfx/gl3/DeviceGL.hpp"

#include <map>

namespace xe { namespace gfx { namespace gl3 {

    static std::map<int, xe::input::KeyCode> keymaps = {
        {GLFW_KEY_ESCAPE    , xe::input::KeyCode::KeyEsc},
        {GLFW_KEY_LEFT      , xe::input::KeyCode::KeyLeft},
        {GLFW_KEY_RIGHT     , xe::input::KeyCode::KeyRight},
        {GLFW_KEY_UP        , xe::input::KeyCode::KeyUp},
        {GLFW_KEY_DOWN      , xe::input::KeyCode::KeyDown},
        {GLFW_KEY_ENTER     , xe::input::KeyCode::KeyEnter}, 
        {GLFW_KEY_SPACE     , xe::input::KeyCode::KeySpace}
    };

    void xe_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_REPEAT) {
            return;
        }
        
        auto driver = static_cast<xe::gfx::gl3::DeviceGL*>(::glfwGetWindowUserPointer(window));
        auto manager = static_cast<InputManagerGLFW*>(driver->getInputManager());

        // determine key code
        auto code = xe::input::KeyCode::Unknown;

        auto keyIterator = keymaps.find(key);
        if (keyIterator != keymaps.end()) {
            code = keyIterator->second;
        }

        if (code == xe::input::KeyCode::Unknown) {
            return;
        }

        // determine key status
        auto status = xe::input::KeyStatus::Release;
        
        switch (action) {
            case GLFW_RELEASE:  status = xe::input::KeyStatus::Release;    break;
            case GLFW_PRESS:    status = xe::input::KeyStatus::Press;      break;
        }
        
        // set the key status
        manager->getKeyboard()->getStatus()->setKeyStatus(code, status);
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
