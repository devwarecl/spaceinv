
#pragma once

#ifndef __gl3_device__
#define __gl3_device__

#include <cassert>
#include "OpenGL.hpp"
#include "ProgramGL.hpp"
#include "MeshGL.hpp"

#include "xe/gfx/Device.hpp"
#include "xe/gfx/UniformFormat.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class DeviceGL : public Device {
    public:
        DeviceGL();

        virtual ~DeviceGL();

        virtual int getKey(int key) const  override;

		virtual void pollEvents()  override;

		virtual MeshPtr createMesh(const MeshFormat &format, std::vector<BufferPtr> buffers)  override;

        virtual BufferPtr createBuffer(const BufferType type, const std::size_t size, const void *data)  override;

		virtual TexturePtr createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData)  override;

		virtual ProgramPtr createProgram(const std::list<ShaderSource> &sources) override;

		virtual void setProgram(Program *program) override;

		virtual Program* getProgram() override {
			return m_program;
		}
		
		virtual void setMaterial(Material *material) override;

		virtual void setMesh(Mesh *mesh) override;

		virtual void render(Primitive primitive, size_t start, size_t count) override;

		virtual void beginFrame(const ClearFlags flags, const ClearParams &params)  override;

		virtual void endFrame()  override;

		virtual void setUniformMatrix(int location, int total, bool transpose, float *values) override {
			glUniformMatrix4fv(location, total, transpose?GL_TRUE:GL_FALSE, values);
		}

		virtual void setUniform(const UniformDescriptor &desc, const void* uniform) override;

		virtual void setUniform(const UniformFormat* format, const void *uniforms) override;

    private:
        GLFWwindow *m_window = nullptr;

		Material *m_material = nullptr;
		MeshGL *m_mesh = nullptr;
		ProgramGL *m_program = nullptr;
    };
}}}

#endif
