#include "VertexArray.h"

unsigned int glAbs::VertexArray::boundId = 0;

void glAbs::VertexArray::push(const IndexBuffer* buffer)
{
    bind();
    buffer->bind();
    unbind();
    buffer->unbind();
    isIndexBuffer = true;
}

void glAbs::VertexArray::bind() const
{
    if (VertexArray::boundId != id)
    {
        VertexArray::boundId = id;
        glCall(glBindVertexArray(id));
        enableAll();
    }
}

void glAbs::VertexArray::unbind() const
{
    if (boundId == id)
    {
        disableAll();
        glCall(glBindVertexArray(0));
        VertexArray::boundId = 0;
    }
}

void
glAbs::VertexArray::push(const VertexBuffer* buffer, const VertexBufferLayout layouts[], unsigned int numberOfLayouts)
{
    bindAndDontEnable();
    buffer->bind();
    for (int i = 0; i < numberOfLayouts; i++)
    {
        indices.insert(layouts[i].attribIndex);
        glCall(glEnableVertexAttribArray(layouts[i].attribIndex));
        glCall(glVertexAttribPointer(layouts[i].attribIndex, layouts[i].numberOfElements, layouts[i].type,
                                     layouts[i].normalized, layouts[i].stride, layouts[i].memberOffset));
    }
    buffer->unbind();
    unbind();
}

void glAbs::VertexArray::disableAll() const
{
    std::set<unsigned int>::iterator itr;
    for (itr = indices.begin(); itr != indices.end(); ++itr)
    {
        glCall(glDisableVertexAttribArray(*itr));
    }
}

void glAbs::VertexArray::enableAll() const
{
    std::set<unsigned int>::iterator itr;
    for (itr = indices.begin(); itr != indices.end(); ++itr)
    {
        glCall(glEnableVertexAttribArray(*itr));
    }
}

void glAbs::VertexArray::unbindAndDontDisable() const
{
    if (boundId == id)
    {
        glCall(glBindVertexArray(0));
        VertexArray::boundId = 0;
    }
}

void glAbs::VertexArray::bindAndDontEnable() const
{
    if (boundId != id)
    {
        glCall(glBindVertexArray(id));
        VertexArray::boundId = id;
    }
}

glAbs::VertexArray::VertexArray(unsigned int numberOfIndices) : numberOfIndices(numberOfIndices),
                                                       id(0)
{
    glCall(glGenVertexArrays(1, &id));
}

glAbs::VertexArray::VertexArray(const VertexArray& va) : id(va.id),
                                                         indices(va.indices),
                                                         isIndexBuffer(va.isIndexBuffer),
                                                         numberOfIndices(va.numberOfIndices) {}

glAbs::VertexArray::VertexArray(VertexArray&& va) noexcept: indices(std::move(va.indices)),
                                                            numberOfIndices(va.numberOfIndices)
{
    id = va.id;
    va.id = 0;
}

glAbs::VertexArray& glAbs::VertexArray::operator=(glAbs::VertexArray&& va) noexcept
{
    id = va.id;
    va.id = 0;
    indices = std::move(va.indices);
    isIndexBuffer = va.isIndexBuffer;
    numberOfIndices = va.numberOfIndices;
    return *this;
}

glAbs::VertexArray::VertexArray() : numberOfIndices(0),
                                    id(0) {}

//glAbs::VertexArray& glAbs::VertexArray::operator=(glAbs::VertexArray va) noexcept
//{
//    id = va.id;
//    indices = va.indices;
//    isIndexBuffer = va.isIndexBuffer;
//    numberOfIndices = va.numberOfIndices;
//    return *this;
//}