
#pragma once

#ifndef __xe_gfx_device_hpp__
#define __xe_gfx_device_hpp__

#include "xe/Buffer.hpp"
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
	};

    class Device {
    public:
        virtual ~Device() {}

		virtual ProgrammableUnit* getProgrammableUnit() = 0;

		virtual void pollEvents() = 0;

        virtual BufferPtr createBuffer(BufferType type, std::size_t size, void* data=nullptr) = 0;

    };
}}

#endif
