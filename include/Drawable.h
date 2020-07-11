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
    private:
        int numberOfVertices;
        int numberOfIndices;
        Vertex* vertices;
        unsigned int* indices;

        bool isRendererSetup = false;

    public:
        const Window* window = MainWindow::getInstance();
        const Renderer* renderer;

        template<int numberOfVertices, int numberOfIndices>
        Drawable(Vertex[numberOfVertices] vertices, unsigned int[numberOfIndices] indices, Renderer* renderer);

        int getNumberOfVertices();

        virtual void draw();
    };
}


#endif //ACGL_ABSTRACTION_DRAWABLE_H
