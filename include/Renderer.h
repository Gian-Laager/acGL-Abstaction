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
    enum DrawMode
    {
        VERTEX_ARRAY, VERTEX_BUFFER, VERTEX_AND_INDEX_BUFFER
    };

    class Renderer
    {
    private:
        DrawMode drawMode;
    public:
        VertexArray* vao = nullptr;
        Shader* shader = nullptr;
        IndexBuffer* ibo = nullptr;
        VertexBuffer* vbo = nullptr;
        VertexBufferLayout* layouts = nullptr;
        unsigned int numberOfLayouts = 0;

        Renderer(VertexArray* vao, Shader* shader);

        Renderer(VertexBuffer* vbo, IndexBuffer* ibo, VertexBufferLayout* layouts, unsigned int numberOfLayouts,
                 Shader* shader);

        Renderer(VertexBuffer* vbo, VertexBufferLayout* layouts, unsigned int numberOfLayouts,
                 Shader* shader);

        void draw(int numberOfVertecies);

        void draw();

        void draw(void* offset);

        void draw(int numberOfVertecies, void* offset);

        void draw(unsigned int numberOfVertecies, GLenum mode);

        void draw(GLenum mode);

        void draw(void* offset, GLenum mode);

        void draw(int numberOfVertecies, void* offset, GLenum mode);
    };
}