//
// Created by Gian Laager on 10.07.20.
//

#include "VertexIndexBufferRenderer.h"

void glAbs::VertexIndexBufferRenderer::bind() const
{
    VertexBufferRenderer::bind();
    indexBuffer->bind();
}

void glAbs::VertexIndexBufferRenderer::unbind() const
{
    VertexBufferRenderer::unbind();
    indexBuffer->unbind();
}

glAbs::VertexIndexBufferRenderer::VertexIndexBufferRenderer(glAbs::VertexBuffer* vertexBuffer,
                                                            glAbs::IndexBuffer* indexBuffer, glAbs::Shader* shader,
                                                            glAbs::VertexBufferRenderSettings* settings): VertexBufferRenderer(vertexBuffer,
                                                                                                                               shader, settings),
                                                                                                          indexBuffer(
                                                                                                                  indexBuffer) {}

void glAbs::VertexIndexBufferRenderer::draw() const
{
    bind();
    glCall(glDrawElements(settings->drawMode, settings->numberOfIndices, GL_UNSIGNED_INT, settings->offset));
    unbind();
}
