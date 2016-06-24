
#pragma once

#ifndef __gl3_device__
#define __gl3_device__

#include <cassert>
#include "GL.hpp"
#include "ProgramGL.hpp"
#include "MeshGL.hpp"

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"

namespace gl3 {

	struct UniformDescriptor : public xe::Attrib {
		int location = -1;	//! Location
		int size = 0;		//! How many elements has the array

		size_t getSize() const {
			return size * xe::Attrib::getSize();
		}
	};
	
	typedef xe::DataFormat<UniformDescriptor> UniformFormat;

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

        void setUniform(GLint location, float v) {
			// assert(location > 0);
            glUniform1f(location, v);
        }

        void setUniform(GLint location, float v1, float v2) {
			// assert(location > 0);
            glUniform2f(location, v1, v2);
        }

        void setUniform(GLint location, float v1, float v2, float v3) {
			// assert(location > 0);
            glUniform3f(location, v1, v2, v3);
        }

        void setUniform(GLint location, float v1, float v2, float v3, float v4) {
			// assert(location > 0);
            glUniform4f(location, v1, v2, v3, v4);
        }
        
        void setUniform(GLint location, int v) {
			// assert(location > 0);
            glUniform1i(location, v);
        }

        void setUniform(GLint location, int v1, int v2) {
			// assert(location > 0);
            glUniform2i(location, v1, v2);
        }

        void setUniform(GLint location, int v1, int v2, int v3) {
			// assert(location > 0);
            glUniform3i(location, v1, v2, v3);
        }

        void setUniform(GLint location, int v1, int v2, int v3, int v4) {
			// assert(location > 0);
            glUniform4i(location, v1, v2, v3, v4);
        }

        void setUniform1(GLint location, int total, const float *values) {
			// assert(location > 0);
            glUniform1fv(location, total, values);
        }

        void setUniform2(GLint location, int total, const float *values) {
			// assert(location > 0);
            glUniform2fv(location, total, values);
        }

        void setUniform3(GLint location, int total, const float *values) {
			// assert(location > 0);
            glUniform3fv(location, total, values);
        }

        void setUniform4(GLint location, int total, const float *values) {
			// assert(location > 0);
            glUniform4fv(location, total, values);
        }

        void setUniform1(GLint location, int total, const int *values) {
			// assert(location > 0);
            glUniform1iv(location, total, values);
        }

        void setUniform2(GLint location, int total, const int *values) {
			// assert(location > 0);
            glUniform2iv(location, total, values);
        }

        void setUniform3(GLint location, int total, const int *values) {
			// assert(location > 0);
            glUniform3iv(location, total, values);
        }

        void setUniform4(GLint location, int total, const int *values) {
			// assert(location > 0);
            glUniform4iv(location, total, values);
        }

        void setUniformMatrix(GLint location, int total, bool transpose, float *values) {
			// assert(location > 0);
            glUniformMatrix4fv(location, total, transpose?GL_TRUE:GL_FALSE, values);
        }

		void setUniform(const UniformFormat& format, void *uniforms);

    private:
        GLFWwindow *window = nullptr;
    };
}

#endif
