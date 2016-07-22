
#pragma once

#ifndef __gl3_texturebuffergl__
#define __gl3_texturebuffergl__

#include "xe/Buffer.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class TextureGL;
    class TextureBufferGL : public xe::Buffer {
    public:
        explicit TextureBufferGL(TextureGL *texture) : m_texture(texture) {}

        virtual ~TextureBufferGL() {}

        virtual std::size_t getSize() const override;

        virtual void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const override;

        virtual void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) override;

    private:
        TextureGL *m_texture = nullptr;
    };
}}}

#endif 
