
#pragma once

namespace xe {
	template<typename Enum>
	class Flags {
	public:
		Flags(Enum value) {
			m_flags = value;
		}

		void toggle(Enum flag) {
			m_flags ^= flag;
		}

		bool isEnabled(Enum flag) const {
			if (m_flags & flag) {
				return true;
			} else {
				return false;
			}
		}

		void enable(Enum flag) {
			m_flags |= flag;
		}

		void disable(Enum flag) {
			if (this->isEnabled(flag)) {
				this->toggle(flag);
			}
		}

	private:
		int m_flags = 0;
	};
}
