#ifndef ACGL_ABSTRACTION_DRAWABLE_H
#define ACGL_ABSTRACTION_DRAWABLE_H

#include "pch.h"

#include "Renderer.h"
#include "Window.h"

namespace glAbs
{
    template <typename Vertex>
    class Drawable
    {
    protected:
        int numberOfVertices;

    public:
        const Vertex* vertices;
        const Window* window = MainWindow::getInstance();
        const Renderer* renderer;

        Drawable(Vertex* vertices, const Renderer* renderer);

        template<int numberOfVertices>
        Drawable(std::array<Vertex, numberOfVertices> vertices, const Renderer* renderer);

        int getNumberOfVertices();

        virtual void draw();
    };

    template <typename Vertex>
    std::tuple<VertexBuffer, IndexBuffer> createBuffers(Vertex* vertices, int numberOfVertices);
}


#endif //ACGL_ABSTRACTION_DRAWABLE_H
