#include "IndexBuffer.h"

using namespace glAbs;

unsigned int IndexBuffer::boundId = 0;

IndexBuffer::IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {}

void IndexBuffer::bind() const
{
    if (IndexBuffer::boundId != id)
    {
        Buffer::bind();
        IndexBuffer::boundId = id;
    }
}

void IndexBuffer::unbind() const
{
    if (IndexBuffer::boundId == id)
    {
        Buffer::unbind();
        IndexBuffer::boundId = 0;
    }
}

void glAbs::IndexBuffer::data(void* data, unsigned int numberOfIndices, GLenum usage)
{
    Buffer::data(data, numberOfIndices * sizeof(unsigned int), usage);
}

