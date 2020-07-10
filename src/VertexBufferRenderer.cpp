//
// Created by Gian Laager on 10.07.20.
//

#include "VertexBufferRenderer.h"

glAbs::VertexBufferRenderSettings::VertexBufferRenderSettings(glAbs::VertexBufferLayout* layouts, unsigned int numberOfLayouts,
                                                              unsigned int numberOfIndices) : RenderSettings(
        numberOfIndices),
                                                                                              layouts(layouts),
                                                                                              numberOfLayouts(
                                                                                                      numberOfLayouts) {}

void glAbs::VertexBufferRenderer::bind() const
{
    //TODO: avoid using temporary vertex array
//    for (int i = 0; i < settings->numberOfLayouts; i++)
//    {
//        glCall(glEnableVertexAttribArray(settings->layouts[i].attribIndex));
//        glCall(glVertexAttribPointer(settings->layouts[i].attribIndex, settings->layouts[i].numberOfElements,
//                                     settings->layouts[i].type,
//                                     settings->layouts[i].normalized, settings->layouts[i].stride,
//                                     settings->layouts[i].memberOffset));
//    }
    temp_va = VertexArray(settings->numberOfIndices);
    temp_va.push(vertexBuffer, settings->layouts, settings->numberOfLayouts);
    temp_va.bind();
    shader->bind();
    vertexBuffer->bind();
}

void glAbs::VertexBufferRenderer::unbind() const
{
    for (int i = 0; i < settings->numberOfLayouts; i++)
    {
        glCall(glDisableVertexAttribArray(settings->layouts[i].attribIndex));
    }
    vertexBuffer->unbind();
    shader->unbind();
}

void glAbs::VertexBufferRenderer::draw() const
{
    bind();
    glCall(glDrawArrays(settings->drawMode, (long) settings->offset, settings->numberOfIndices));
    unbind();
}

glAbs::VertexBufferRenderer::VertexBufferRenderer(glAbs::VertexBuffer* vertexBuffer, glAbs::Shader* shader,
                                                  glAbs::VertexBufferRenderSettings* settings) : Renderer(
                                                                                                         shader,
                                                                                                         settings),
                                                                                                 vertexBuffer(
                                                                                                         vertexBuffer),
                                                                                                 settings(settings) {}