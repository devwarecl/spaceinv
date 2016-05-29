
#pragma once

#ifndef __gl3_buffer__
#define __gl3_buffer__

#include <memory>
#include <cassert>
#include "GL.hpp"

namespace gl3 {

    class Buffer {
    public:
        Buffer() {}

        Buffer(GLenum target_, GLenum usage, std::size_t size_, const void *data=nullptr) {
            construct(target_, usage, size_, data);
        }

        template<typename Container>
        Buffer(GLenum target_, GLenum usage, const Container& values) {
            typedef typename Container::value_type Type;

            construct(target_, usage, sizeof(Type) * values.size(), values.data());
        }

        ~Buffer() {
            if (id) {
                glDeleteBuffers(1, &id);
                id = 0;
            }

            assert(glGetError() == GL_NO_ERROR);
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

    protected:
        void construct(GLenum target_, GLenum usage, std::size_t size_, const void *data=nullptr) {
            size = size_;
            target = target_;

            glGenBuffers(1, &id);
            glBindBuffer(target, id);
            glBufferData(target, size, nullptr, usage);
            glBindBuffer(target, 0);

            assert(glGetError() == GL_NO_ERROR);

            if (data) {
                this->write(data);
            }
        }

    private:
        GLenum target;
        GLuint id = 0;
        std::size_t size = 0;
    };
    
    typedef std::unique_ptr<Buffer> BufferPtr;
    typedef std::vector<BufferPtr> BufferVector;
}

#endif
