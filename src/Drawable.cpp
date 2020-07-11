//
// Created by Gian Laager on 06.07.20.
//

#include "Drawable.h"

namespace glAbs
{
    template<typename Vertex>
    int Drawable<Vertex>::getNumberOfVertices()
    {
        return 0;
    }

    template<typename Vertex>
    void Drawable<Vertex>::draw()
    {
    }

    template <typename Vertex>
    std::tuple<VertexBuffer, IndexBuffer> createBuffers(Vertex* vertices, int numberOfVertices)
    {

    }
}