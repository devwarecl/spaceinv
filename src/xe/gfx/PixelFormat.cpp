
#include "PixelFormat.hpp"

namespace xe { namespace gfx {
	size_t size(PixelFormat format) {
		switch (format) {
		case PixelFormat::R5G5B5X1:
		case PixelFormat::R5G5B5A1:
		case PixelFormat::R5G6B5:
			return 16;

		case PixelFormat::B8G8R8:
		case PixelFormat::R8G8B8:
			return 24;

		case PixelFormat::R8G8B8A8:
		case PixelFormat::B8G8R8A8:
			return 32;

		default:
			return 0;
		}
	}
}}
