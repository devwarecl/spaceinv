
#pragma once

#include <vector>

#include "xe/Flags.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/Texture.hpp"

namespace xe { namespace gfx {

    enum class TextureFilter {
        Linear,
        Nearest
    };
    
    enum class TextureWrap {
        Clamp,
        Repeat
    };
    
    struct MaterialLayer {
        Texture *texture = nullptr;

        TextureFilter magFilter = TextureFilter::Linear;
        TextureFilter minFilter = TextureFilter::Linear;
        
        TextureWrap xWrap = TextureWrap::Repeat;
        TextureWrap yWrap = TextureWrap::Repeat;
        TextureWrap zWrap = TextureWrap::Repeat;
        TextureWrap wWrap = TextureWrap::Repeat;

		MaterialLayer() {}
		explicit MaterialLayer(Texture *texture_) : texture(texture_) {}
    };
    
	struct Material {
		enum Enum {
			None = 0,
			CullFace = 2,
			DepthTest = 4,
			Blending = 8
		};

		Flags<Enum> flags = None;

		std::vector<MaterialLayer> layers;

		UniformFormat *format = nullptr;
		void* uniforms = nullptr;

		explicit Material(UniformFormat *format) {
			this->format = format;
		}
	};
}}
