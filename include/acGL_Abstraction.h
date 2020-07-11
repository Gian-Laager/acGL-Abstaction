#ifndef GL_ABSTRACTION_ACGL_ABSTRACTION_H
#define GL_ABSTRACTION_ACGL_ABSTRACTION_H

#include "pch.h"

#include "VertexBufferRenderer.h"
#include "VertexArrayRenderer.h"
#include "Window.h"

namespace glAbs
{
    bool glfwInitialized = false;
    bool glewInitialized = false;

    void hello_GL();

    glAbs::Destroyer init();
}

#endif //GL_ABSTRACTION_ACGL_ABSTRACTION_H
