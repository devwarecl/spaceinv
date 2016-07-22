
#pragma once

#ifndef __xe_gfx_gl3_device__
#define __xe_gfx_gl3_device__

#include <cassert>

#include "xe/gfx/Device.hpp"
#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/gl3/InputManagerGLFW.hpp"
#include "xe/gfx/gl3/OpenGL.hpp"
#include "xe/gfx/gl3/ProgramGL.hpp"
#include "xe/gfx/gl3/MeshGL.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class DeviceGL : public Device {
    public:
        DeviceGL();

        virtual ~DeviceGL();

        virtual xe::input::InputManager* getInputManager() override {
            return &m_inputManager;
        }

        virtual const xe::input::InputManager* getInputManager() const override {
            return &m_inputManager;
        }

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

        virtual void setUniformMatrix(int location, int total, bool transpose, float *values) override;

        virtual void setUniform(const UniformDescriptor &desc, const void* uniform) override;

        virtual void setUniform(const UniformFormat* format, const void *uniforms) override;

    private:
        GLFWwindow *m_window = nullptr;

        Material *m_material = nullptr;
        MeshGL *m_mesh = nullptr;
        ProgramGL *m_program = nullptr;

        InputManagerGLFW m_inputManager;
    };
}}}

#endif
