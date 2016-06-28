#pragma once 

#include <xe/PreDef.hpp>
#include <xe/Vector.hpp>
#include <xe/input/InputDevice.hpp>
#include <xe/input/KeyStatus.hpp>

namespace xe { namespace input {

	enum class MouseButton {
		Unknown,
		ButtonLeft,
		ButtonRight,
		ButtonMiddle,
		Button1 = ButtonLeft,
		Button2 = ButtonRight,
		Button3 = ButtonMiddle,
		Button4 = ButtonMiddle,
		Button5 = ButtonMiddle,
		Button6 = ButtonMiddle,
		Button7 = ButtonMiddle,
		Button8 = ButtonMiddle,
		Total
	};

	class MouseStatus {
	public:
		MouseStatus() {}

		Vector2i getPositionDelta() const {
			return current.position - previous.position;
		}

		Vector2i getPosition() const {
			return current.position;
		}

		void setPosition(const Vector2i &position) {
			previous.position = current.position;
			current.position = position;
		}

		KeyStatus getButtonStatus(MouseButton button) const {
			return current.status[static_cast<int>(button)];
		}

		bool isButtonPressed(MouseButton button) const {
			return current.isPressed(button);
		}

		bool isButtonReleased(MouseButton button) const {
			return current.isReleased(button);
		}

		bool isButtonPushed(MouseButton button) const {
			return current.isPressed(button) && previous.isReleased(button);
		}

		bool isButtonPopped(MouseButton button) const {
			return current.isReleased(button) && previous.isPressed(button);
		}

	private:
		struct Status {
			Vector2i position;
			KeyStatus status[static_cast<int>(MouseButton::Total)] = {};

			bool isPressed(MouseButton button) const {
				return status[static_cast<int>(button)] == KeyStatus::Press;
			}

			bool isReleased(MouseButton button) const {
				return status[static_cast<int>(button)] == KeyStatus::Release;
			}
		};

		Status current;
		Status previous;
	};

	class EXENGAPI Mouse : public InputDevice {
	public:
		virtual ~Mouse() {}

		virtual MouseStatus getStatus() = 0;
	};
}}
