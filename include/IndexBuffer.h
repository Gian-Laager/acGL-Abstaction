#pragma once

#include "Buffer.h"

namespace glAbs
{
    class IndexBuffer : public Buffer
    {
    public:
        static unsigned int boundId;

        IndexBuffer();

        void bind() const override;

        void unbind() const override;

        void data(void* data, unsigned int numberOfIndices, GLenum usage) override;
    };
}
