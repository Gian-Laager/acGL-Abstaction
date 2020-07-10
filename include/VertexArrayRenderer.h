//
// Created by Gian Laager on 10.07.20.
//

#ifndef ACGL_ABSTRACTION_VERTEXARRAYRENDERER_H
#define ACGL_ABSTRACTION_VERTEXARRAYRENDERER_H

#include "pch.h"
#include "Renderer.h"

namespace glAbs
{
    class VertexArrayRenderer : public Renderer
    {
    protected:
        void bind() const override;

        void unbind() const override;

    public:
        VertexArray* vertexArray;

        VertexArrayRenderer(VertexArray* vertexArray, Shader* shader, RenderSettings* settings);

        void draw() const override;
    };
}


#endif //ACGL_ABSTRACTION_VERTEXARRAYRENDERER_H