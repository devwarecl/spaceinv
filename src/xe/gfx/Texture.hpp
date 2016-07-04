
#pragma once

#ifndef __xe_gfx_texture__
#define __xe_gfx_texture__

#include <memory>
#include "xe/Buffer.hpp"
#include "xe/gfx/PixelFormat.hpp"

namespace xe { namespace gfx {

	enum class TextureType {
		Unknown,
		Tex1D,
		Tex2D,
		Tex3D,
		TexCube
	};

	enum class TextureCubeSide {
		Unknown,
		PosX, PosY, PosZ,
		NegX, NegY, NegZ
	};

	struct TextureDesc {
		TextureType type = TextureType::Unknown;
		PixelFormat format = PixelFormat::Unknown;
		size_t width = 0;
		size_t height = 0;
		size_t depth = 0;

		size_t getSize() const {
			size_t result = 1;
			size_t dimensions[] = {width, height, depth};

			for (size_t dim : dimensions) {
				if (dim) {
					result *= dim;
				}
			}

			result *= size(format);

			return result;
		}
	};

	class Texture {
	public:
		virtual ~Texture() {}

		virtual TextureDesc getDesc() const = 0;
		virtual Buffer* getBuffer(TextureCubeSide side = TextureCubeSide::Unknown, size_t level = 0) = 0;
		virtual const Buffer* getBuffer(TextureCubeSide side = TextureCubeSide::Unknown, size_t level = 0) const = 0;

		virtual void buildMipmaps();

		static void generateCheckerboard(Texture *texture, const int tilesInX, const int tilesInY);
	};

	typedef std::unique_ptr<Texture> TexturePtr;
}}

#endif
