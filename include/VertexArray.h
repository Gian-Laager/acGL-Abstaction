#pragma once

#include "pch.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace glAbs
{
    class VertexArray
    {
    private:
        void addVertexAttrib(const VertexBufferLayout& layout);
    public:
        unsigned int id;

        static unsigned int boundId;

        std::set<unsigned int> indices;

        bool isIndexBuffer = false;

        unsigned int numberOfIndices;

        VertexArray();

        VertexArray(unsigned int numberOfIndices);

        void push(const IndexBuffer* buffer);

        void push(const VertexBuffer* buffer, const VertexBufferLayout* layouts, unsigned int numberOfLayouts);

        void bind() const;

        void unbind() const;

        void bindAndDontEnable() const;

        void unbindAndDontDisable() const;

        VertexArray(const VertexArray& va);

        VertexArray(VertexArray&& va) noexcept;

        VertexArray& operator=(VertexArray&& va) noexcept;

//        VertexArray& operator=(VertexArray va) noexcept;

    private:
        void disableAll() const;

        void enableAll() const;
    };
}