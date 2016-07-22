
#include <xe/input/KeyboardStatus.hpp>

#include <cstring>
#include <iostream>

namespace xe { namespace input {
    KeyboardStatus::KeyboardStatus() {}

    void KeyboardStatus::setKeyStatus(KeyCode keyCode, KeyStatus keyStatus) {
        const auto index = static_cast<int>(keyCode);

        m_previous.status[index] = m_current.status[index];
        m_current.status[index] = keyStatus;

        if (keyCode == KeyCode::KeySpace) {
            std::cout << "KeyboardStatus::setKeyStatus:" << std::endl;
            std::cout 
                << "    key: " << static_cast<int>(keyCode)
                << ", status: " << static_cast<int>(keyStatus)
                << ", previus: " << static_cast<int>(m_current.status[static_cast<int>(keyCode)])
                << std::endl;
        }
    }

    KeyStatus KeyboardStatus::getKeyStatus(KeyCode keyCode) const {
        return m_current.status[static_cast<int>(keyCode)];
    }

    bool KeyboardStatus::isKeyPressed(KeyCode keyCode) const {
        return m_current.isPressed(keyCode);
    }

    bool KeyboardStatus::isKeyReleased(KeyCode keyCode) const {
        return m_current.isReleased(keyCode);
    }

    bool KeyboardStatus::isKeyPushed(KeyCode keyCode) const {
        const bool result = m_current.isPressed(keyCode) && m_previous.isReleased(keyCode);

        return result;
    }

    bool KeyboardStatus::isKeyPopped(KeyCode keyCode) const {
        const bool result = m_current.isReleased(keyCode) && m_previous.isPressed(keyCode);

        return result;
    }
}}
