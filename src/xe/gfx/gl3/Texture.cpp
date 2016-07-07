
#include <iostream>
#include <vector>

#include "xe/Vector.hpp"
#include "xe/gfx/Texture.hpp"
#include "xe/gfx/Device.hpp"

namespace xe { namespace gfx {
	void Texture::buildMipmaps() {
		std::cout << "Texture::buildMipmaps: Not Implemented" << std::endl;
	}

	TexturePtr Texture::createCheckerboard(Device *device, const TextureDesc &desc, const int tilesInX, const int tilesInY) {
		assert(device);
		assert(tilesInX > 0);
		assert(tilesInY > 0);

		auto pixelFormat = PixelFormat::R8G8B8;
		auto pixelArray = std::vector<uint8_t>(desc.width * desc.height * size(pixelFormat));
		auto pixels = pixelArray.data();
		
		const int tileWidth = desc.width / tilesInX;
		const int tileHeight = desc.height / tilesInY;

		for (size_t row=0; row<desc.height; row++) {
			for (size_t col=0; col<desc.width; col++) {
				const bool colBool = ((col&tileWidth) == 0);
				const bool rowBool = ((row&tileHeight) == 0);
				const int color = static_cast<int>(rowBool^colBool) * 255;

				*pixels++ = color;
				*pixels++ = color;
				*pixels++ = color;
			}
		}

		return device->createTexture(desc, pixelFormat, DataType::UInt8, pixels);
	}
}}
