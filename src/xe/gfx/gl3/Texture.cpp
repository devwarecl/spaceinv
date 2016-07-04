
#include <iostream>
#include <vector>

#include "xe/Vector.hpp"
#include "xe/gfx/Texture.hpp"

namespace xe { namespace gfx {
	void Texture::buildMipmaps() {
		std::cout << "Texture::buildMipmaps: Not Implemented" << std::endl;
	}

	template<typename VectorType>
	void generateCheckerboardTexture(Texture *texture, const int row, const int col, const int tileWidth, const int tileHeight) {
		const int PixelDimension = VectorType::Size;
		typedef typename VectorType::Type Type;

		const bool colBool = ((col&tileWidth) == 0);
		const bool rowBool = ((row&tileHeight) == 0);
		const int color = static_cast<int>(rowBool^colBool) * 255;

		for (int i=0; i<PixelDimension; i++) {
			pixel->values[i] = static_cast<Type>(color);
		}

		if (PixelDimension == 4) {
			pixel->values[3] = static_cast<Type>(255);
		}
	}

	void Texture::generateCheckerboard(Texture *texture, const int tilesInX, const int tilesInY) {
		assert(texture);
		assert(tilesInX > 0);
		assert(tilesInY > 0);
		
		const TextureDesc desc = texture->getDesc();

		std::vector<uint8_t> textureData(desc.getSize());
		
		for (int row=0; row<desc.height; row++) {
			for (int col=0; col<desc.width; col++) {

				switch (desc.format) {
				case xe::gfx::PixelFormat::R8G8B8:
				case xe::gfx::PixelFormat::B8G8R8:

					auto pixels = static_cast<xe::Vector<std::uint8_t, 3>>(textureData.)

					break;

				case xe::gfx::PixelFormat::B8G8R8A8:
				case xe::gfx::PixelFormat::R8G8B8A8:

					break;
				}

				bool rowBool = ((row&tileSize.y) == 0);
				bool colBool = ((col&tileSize.x) == 0);
    
				int c = ((int)(rowBool^colBool))*255;
    
				pixels->x = (std::uint8_t) c;
				pixels->y = (std::uint8_t) c;
				pixels->z = (std::uint8_t) c;
	
				++pixels;
			}
		}
	}
}}
