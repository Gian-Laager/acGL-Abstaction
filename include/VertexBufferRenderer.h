//
// Created by Gian Laager on 10.07.20.
//

#ifndef ACGL_ABSTRACTION_VERTEXBUFFERRENDERER_H
#define ACGL_ABSTRACTION_VERTEXBUFFERRENDERER_H

#include "pch.h"
#include "Renderer.h"

namespace glAbs
{
    struct VertexBufferRenderSettings : RenderSettings
    {
        VertexBufferRenderSettings(VertexBufferLayout* layouts,
                                   unsigned int numberOfLayouts, unsigned int numberOfIndices);

        VertexBufferLayout* layouts;
        unsigned int numberOfLayouts;
    };

    class VertexBufferRenderer : public Renderer
    {
    private:
        void createNewTemp_va(VertexBuffer* vertexBuffer) const;

    protected:
        void unbind() const override;

        void bind() const override;

    public:
        VertexBuffer* vertexBuffer;
        VertexBufferRenderSettings* settings;
        mutable VertexArray temp_va;

        VertexBufferRenderer(VertexBuffer* vertexBuffer, Shader* shader, VertexBufferRenderSettings* settings);

        void draw() const override;
    };
}

#endif //ACGL_ABSTRACTION_VERTEXBUFFERRENDERER_H