//
// Created by Gian Laager on 10.07.20.
//

#ifndef ACGL_ABSTRACTION_VERTEXINDEXBUFFERRENDERER_H
#define ACGL_ABSTRACTION_VERTEXINDEXBUFFERRENDERER_H

#include "pch.h"
#include "VertexBufferRenderer.h"

namespace glAbs
{
    class VertexIndexBufferRenderer : public VertexBufferRenderer
    {
    protected:
        void bind() const override;

        void unbind() const override;

    public:
        IndexBuffer* indexBuffer;

        VertexIndexBufferRenderer(VertexBuffer* vertexBuffer,
                                  IndexBuffer* indexBuffer, Shader* shader,
                                  VertexBufferRenderSettings* settings
        );

        void draw() const override;
    };
}


#endif //ACGL_ABSTRACTION_VERTEXINDEXBUFFERRENDERER_H
