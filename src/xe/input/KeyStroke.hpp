
#pragma once 

#ifndef __xe_input_keystroke__
#define __xe_input_keystroke__

#include <xe/input/KeyCode.hpp>
#include <xe/input/KeyStatus.hpp>

namespace xe { namespace input {
	struct KeyStroke {
		KeyCode code = KeyCode::Unknown;
		KeyStatus status = KeyStatus::Release;

		KeyStroke() {}
		KeyStroke(KeyCode code_, KeyStatus status_) : code(code_), status(status_) {}
	};
}}

#endif 
