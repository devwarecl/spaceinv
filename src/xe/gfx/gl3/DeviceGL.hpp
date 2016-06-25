
#pragma once

#ifndef __gl3_device__
#define __gl3_device__

#include <cassert>
#include "OpenGL.hpp"
#include "ProgramGL.hpp"
#include "MeshGL.hpp"

#include "xe/gfx/UniformFormat.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class DeviceGL {
    public:
        DeviceGL();

        ~DeviceGL();

		void pollEvents();

        void beginFrame();

        void endFrame();

        int getKey(int key) const;

        void setProgram(const ProgramGL *program);

        void setSubset(const MeshGL *subset);

        void render(const MeshGL *subset, GLenum primitive, std::size_t count);

        void render(const MeshGL *subset, GLenum primitive, size_t start, size_t count);

        void setUniformMatrix(GLint location, int total, bool transpose, float *values) {
			// assert(location > 0);
            glUniformMatrix4fv(location, total, transpose?GL_TRUE:GL_FALSE, values);
        }

		void setUniform(const UniformDescriptor &desc, void* uniform);

		void setUniform(const UniformFormat& format, void *uniforms);

		template<typename Type>
		void setUniform(const int location, const int count, const Type *values, const int size) {
			UniformDescriptor desc;

			desc.type = xe::getDataType<Type>();
			desc.count = count;
			desc.location = location;
			desc.size = size;

			this->setUniform(desc, values);
		}

		template<typename Type>
		void setUniform(const int location, const int count, const Type value) {
			this->setUniform(location, count, &value, 1);
		}

    private:
        GLFWwindow *window = nullptr;
    };
}}}

#endif
