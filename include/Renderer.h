#pragma once

#include "pch.h"

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"


namespace glAbs
{
    struct RenderSettings
    {
        RenderSettings(unsigned int numberOfIndices);
        unsigned int numberOfIndices;
        GLenum drawMode = GL_TRIANGLES;
        void* offset = nullptr;
    };

    class Renderer
    {
    protected:
        Renderer(Shader* shader, RenderSettings* settings);
        virtual void bind() const = 0;
        virtual void unbind() const = 0;

    public:
        Shader* shader = nullptr;
        RenderSettings* settings;

//        Renderer(VertexArray* vao, Shader* shader); VertexArrayRenderer
//
//        Renderer(VertexBuffer* vbo, IndexBuffer* ibo, VertexBufferLayout* layouts, unsigned int numberOfLayouts,
//                 Shader* shader); VertexIndexBufferRenderer
//
//        Renderer(VertexBuffer* vbo, VertexBufferLayout* layouts, unsigned int numberOfLayouts,
//                 Shader* shader); VertexBufferRenderer

        virtual void draw() const = 0;
    };
}