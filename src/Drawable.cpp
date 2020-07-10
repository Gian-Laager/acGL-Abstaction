//
// Created by Gian Laager on 06.07.20.
//

#include "Drawable.h"

namespace glAbs
{
    template<typename Vertex>
    Drawable<Vertex>::Drawable(Vertex* vertices, int numberOfVertices) : numberOfVertices(numberOfVertices), vertices(vertices)
    {

    }

    template<typename Vertex>
    template<int t_numberOfVertices>
    Drawable<Vertex>::Drawable(std::array<Vertex, t_numberOfVertices> vertices) : numberOfVertices(t_numberOfVertices)
    {

    }

    template<typename Vertex>
    int Drawable<Vertex>::getNumberOfVertices()
    {
        return 0;
    }

    template<typename Vertex>
    void Drawable<Vertex>::draw()
    {
        Renderer::draw();
    }

    template <typename Vertex>
    std::tuple<VertexBuffer, IndexBuffer> createBuffers(Vertex* vertices, int numberOfVertices)
    {
    }
}