

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

    static xe::input::KeyStatus s_status[] = {
        xe::input::KeyStatus::Release,
        xe::input::KeyStatus::Press
    };

    void KeyboardGLFW::poll() {
        if (!window) {
            return;
        }

        for (const auto &pair : keymaps) {
            auto keyStatus = s_status[::glfwGetKey(window, pair.first)];
            
            status.setKeyStatus(pair.second, keyStatus);
        }
    }

    void xe_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_REPEAT) {
            return;
        }
        
        //auto driver = static_cast<xe::gfx::gl3::DeviceGL*>(::glfwGetWindowUserPointer(window));
        //auto manager = static_cast<InputManagerGLFW*>(driver->getInputManager());

        //// determine key code
        //auto code = xe::input::KeyCode::Unknown;

        //auto keyIterator = keymaps.find(key);
        //if (keyIterator != keymaps.end()) {
        //    code = keyIterator->second;
        //}

        //if (code == xe::input::KeyCode::Unknown) {
        //    return;
        //}

        //// determine key status
        //auto status = s_status[action];
        //
        //// set the key status
        //manager->getKeyboard()->getStatus()->setKeyStatus(code, status);
    }

    InputManagerGLFW::InputManagerGLFW() {}

    InputManagerGLFW::InputManagerGLFW(GLFWwindow* window) {
        this->setWindow(window);
    }

    void InputManagerGLFW::poll() {
        ::glfwPollEvents();

        m_keyboard.poll();
    }

    void InputManagerGLFW::setWindow(GLFWwindow *window) {
        ::glfwSetKeyCallback(window, xe_handle_key);

        m_window = window;
        m_keyboard.window = window;
    }
}}}
