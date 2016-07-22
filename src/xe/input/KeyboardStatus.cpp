
#include <xe/input/KeyboardStatus.hpp>

#include <cstring>
#include <iostream>

namespace xe { namespace input {
    KeyboardStatus::KeyboardStatus() {}

    void KeyboardStatus::setKeyStatus(KeyCode keyCode, KeyStatus keyStatus) {
        //std::cout << "KeyboardStatus::setKeyStatus:" << std::endl;
        //std::cout 
        //    << "    key: " << static_cast<int>(keyCode)
        //    << ", status: " << static_cast<int>(keyStatus)
        //    << ", previus: " << static_cast<int>(m_current.status[static_cast<int>(keyCode)])
        //    << std::endl;

        m_previous.status = m_current.status;
        m_current.status[static_cast<int>(keyCode)] = keyStatus;
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
