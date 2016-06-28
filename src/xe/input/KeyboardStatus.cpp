
#include <xe/input/KeyboardStatus.hpp>

#include <cstring>

namespace xe { namespace input {
	KeyboardStatus::KeyboardStatus() {}

	void KeyboardStatus::setKeyStatus(KeyCode keyCode, KeyStatus keyStatus) {
		previous.status = current.status;
		current.status[static_cast<int>(keyCode)] = keyStatus;
	}

	KeyStatus KeyboardStatus::getKeyStatus(KeyCode keyCode) const {
		return current.status[static_cast<int>(keyCode)];
	}

	bool KeyboardStatus::isKeyPressed(KeyCode keyCode) const {
		return current.isPressed(keyCode);
	}

	bool KeyboardStatus::isKeyReleased(KeyCode keyCode) const {
		return current.isReleased(keyCode);
	}

	bool KeyboardStatus::isKeyPushed(KeyCode keyCode) const {
		return current.isPressed(keyCode) && previous.isReleased(keyCode);
	}

	bool KeyboardStatus::isKeyPopped(KeyCode keyCode) const {
		return current.isReleased(keyCode) && previous.isPressed(keyCode);
	}
}}
