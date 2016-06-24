
#pragma once

#ifndef __xe_gfx_device_hpp__
#define __xe_gfx_device_hpp__

#include "xe/Buffer.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/BufferType.hpp"
#include "xe/gfx/Mesh.hpp"
#include "xe/gfx/ShaderType.hpp"
#include "xe/gfx/Program.hpp"
#include "xe/gfx/Texture.hpp"

namespace xe { namespace gfx {

	class ProgrammableUnit {
	public:
		virtual ~ProgrammableUnit() {}

		ProgramPtr createProgram(const ShaderSource &source) {
			std::list<ShaderSource> sources = {source};

			return this->createProgram(sources);
		}

		virtual ProgramPtr createProgram(const std::list<ShaderSource> &sources) = 0;

		virtual void setProgram(Program *program) = 0;

		virtual Program* getProgram() = 0;
	};

	struct ClearData {
		xe::Vector4f color;
		float depth;
		float stencil;

		ClearData(xe::Vector4f color_ = {0.0f, 0.0f, 0.0f, 1.0f}, float depth_ = 0.0f, float stencil_ = 0.0f) 
			: color(color_), depth(depth_), stencil(stencil_){}
	};

	enum class ClearFlags {
		Color = 1,
		Depth = 2,
		Stencil = 4,
		All = Color | Depth | Stencil
	};

    class Device {
    public:
        virtual ~Device() {}

		virtual ProgrammableUnit* getProgrammableUnit() = 0;

		virtual void pollEvents() = 0;

        virtual BufferPtr createBuffer(BufferType type, std::size_t size) = 0;

		virtual TexturePtr createTexture(const TextureDesc &desc) = 0;

		virtual void beginScene(ClearFlags flags=ClearFlags::All, const ClearData &data=ClearData()) = 0;

		virtual void endScene() = 0;
    };
}}

#endif
