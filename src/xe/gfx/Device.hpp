
#pragma once

#ifndef __xe_gfx_device_hpp__
#define __xe_gfx_device_hpp__

#include <list>

#include "xe/Buffer.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/BufferType.hpp"
#include "xe/gfx/Mesh.hpp"
#include "xe/gfx/ShaderType.hpp"
#include "xe/gfx/Program.hpp"
#include "xe/gfx/Texture.hpp"
#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/Material.hpp"
#include "xe/gfx/Primitive.hpp"
#include "xe/input/InputManager.hpp"

namespace xe { namespace gfx {

    struct ClearParams {
        xe::Vector4f color;
        double depth;
        int stencil;

        ClearParams(xe::Vector4f color_ = {0.0f, 0.0f, 0.0f, 1.0f}, double depth_ = 1.0f, int stencil_ = 0) 
            : color(color_), depth(depth_), stencil(stencil_){}
    };

    enum class ClearFlags {
        Color = 1,
        Depth = 2,
        Stencil = 4,
        ColorDepth = Color | Depth,
        All = Color | Depth | Stencil
    };

    inline bool operator&(const ClearFlags flags, const ClearFlags value) {
        int nflags = static_cast<int>(flags);
        int nvalue = static_cast<int>(value);

        if (nflags & nvalue) {
            return true;
        } else {
            return false;
        }
    }

    class Device {
    public:
        virtual ~Device() {}

        virtual xe::input::InputManager* getInputManager() = 0;

        virtual const xe::input::InputManager* getInputManager() const = 0;

        virtual MeshPtr createMesh(const MeshFormat &format, std::vector<BufferPtr> buffers) = 0;

        virtual BufferPtr createBuffer(const BufferType type, const std::size_t size, const void *data=nullptr) = 0;

        template<typename Container>
        BufferPtr  createBuffer(const BufferType type, const Container& values) {
            typedef typename Container::value_type Type;

            return this->createBuffer(type, sizeof(Type) * values.size(), values.data());
        }

        virtual TexturePtr createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData) = 0;

        ProgramPtr createProgram(const ShaderSource &source) {
            std::list<ShaderSource> sources = {source};

            return this->createProgram({source});
        }

        virtual ProgramPtr createProgram(const std::list<ShaderSource> &sources) = 0;

        virtual void setProgram(Program *program) = 0;

        virtual Program* getProgram() = 0;
        
        virtual void setMaterial(Material *material) = 0;

        virtual void setMesh(Mesh *mesh) = 0;

        virtual void render(Primitive primitive, size_t start, size_t count) = 0;

        virtual void beginFrame(const ClearFlags flags=ClearFlags::All, const ClearParams &params=ClearParams()) = 0;

        virtual void endFrame() = 0;

        virtual void setUniformMatrix(int location, int total, bool transpose, float *values) = 0;

        virtual void setUniform(const UniformDescriptor &desc, const void* uniform) = 0;

        virtual void setUniform(const UniformFormat* format, const void *uniforms);

        template<typename Type>
        void setUniform(const int location, const int count, const Type *values, const int size) {
            UniformDescriptor desc;

            desc.type = xe::getDataType<Type>();
            desc.dim = count;
            desc.location = location;
            desc.count = size;

            this->setUniform(desc, values);
        }

        template<typename Type>
        void setUniform(const int location, const int count, const Type value) {
            this->setUniform(location, count, &value, 1);
        }
    };

    typedef std::unique_ptr<Device> DevicePtr;
}}

#endif
