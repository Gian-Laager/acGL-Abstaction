#pragma once

#include "Buffer.h"

namespace glAbs
{
    class IndexBuffer : public Buffer
    {
    public:
        static unsigned int boundId;
        int numberOfVertecies;

        IndexBuffer(int numberOfVertecies);

        void bind() const override;

        void unbind() const override;
    };
}