
#pragma once

#ifndef __gl3_buffer__
#define __gl3_buffer__

#include <cassert>
#include "GL.hpp"

namespace gl3 {
    class Buffer {
    public:
        Buffer() {}

        Buffer(GLenum target_, GLenum usage, std::size_t size_, const void *data=nullptr) {
            size = size_;
            target = target_;

            glGenBuffers(1, &id);
            glBindBuffer(target, id);
            glBufferData(target, size, nullptr, usage);
            glBindBuffer(target, 0);

            assert(glGetError() == GL_NO_ERROR);

            if (data) {
                write(data);
            }
        }

        Buffer(Buffer &&other) {
            *this = std::move(other);
        }

        ~Buffer() {
            if (id) {
                glDeleteBuffers(1, &id);
                id = 0;
            }

            assert(glGetError() == GL_NO_ERROR);
        }

        Buffer& operator= (Buffer &&other) {
            this->~Buffer();

            id = other.id;
            target = other.target;
            size = other.size;

            other.id = 0;
            other.size = 0;

            return *this;
        }

        void write(const void* data) {
            glBindBuffer(target, id);
            glBufferSubData(target, 0, size, data);
            glBindBuffer(target, 0);

            assert(glGetError() == GL_NO_ERROR);
        }

        void read(void *data) const {
            glBindBuffer(target, id);
            glGetBufferSubData(target, 0, size, data);
            glBindBuffer(target, 0);

            assert(glGetError() == GL_NO_ERROR);
        }

        GLint getId() const {
            return id;
        }

        GLenum getTarget() const {
            return target;
        }

        operator bool() const {
            return this->id != 0;
        }

    private:
        GLenum target;
        GLuint id = 0;
        std::size_t size = 0;
    };
}

#endif
