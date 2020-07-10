//
// Created by Gian Laager on 10.07.20.
//

#include "VertexArrayRenderer.h"

glAbs::VertexArrayRenderer::VertexArrayRenderer(glAbs::VertexArray* vertexArray, glAbs::Shader* shader,
                                                glAbs::RenderSettings* settings) : Renderer(shader, settings),
                                                                                   vertexArray(vertexArray) {}

void glAbs::VertexArrayRenderer::draw() const
{
    bind();
    if (vertexArray->isIndexBuffer)
    {
        glCall(glDrawElements(settings->drawMode, settings->numberOfIndices, GL_UNSIGNED_INT, settings->offset));
    } else
    {
        glCall(glDrawArrays(settings->drawMode, (long) settings->offset, settings->numberOfIndices));
    }
    unbind();
}

void glAbs::VertexArrayRenderer::bind() const
{
    vertexArray->bind();
    shader->bind();
}

void glAbs::VertexArrayRenderer::unbind() const
{
    vertexArray->unbind();
    shader->unbind();
}
