#include "acGL_Abstraction.h"

#include "Window.h"

void glAbs::GLErrorHandling::clearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool glAbs::GLErrorHandling::logCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::stringstream errorIdHex;
        errorIdHex << std::hex << error;
        std::cout << "[OpenGL Error] (" << errorIdHex.str() << ") " << "file: " << file << ":" << line << " function: "
                  << function << std::endl;
        return false;
    }
    return true;
}

void glAbs::hello_GL()
{
    struct Vertex
    {
        float x, y;
    };

    Shader* shader;
    Renderer* renderer;
    VertexBufferLayout* positionLayout;
    VertexBuffer* vertexBuffer;

    glfwWindowSettings settings;
//    settings.runMainLoopInParallel = true;

    Window window([&]() {
        const char* versionGL;
        glCall(versionGL = (char*) (glGetString(GL_VERSION)));
        std::cout << "openGl version: " << versionGL << std::endl;

        vertexBuffer = new VertexBuffer();

        Vertex vb_data[] = {
                Vertex{0.5f, -0.5f},
                Vertex{-0.5f, -0.5f},
                Vertex{0.0f, 0.5f}
        };

        vertexBuffer->data(vb_data, sizeof(Vertex) * 3, GL_STATIC_DRAW);

        positionLayout = new VertexBufferLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);

        shader = new Shader("../../../res/shaders/basic2dShader.glsl");

        renderer = new Renderer(vertexBuffer, positionLayout, 1, shader);
    }, [&renderer]() {
        renderer->draw(3);
    }, []() { std::cout << "mainloop finished" << std::endl; }, settings);

    window.runMainLoop();

//    window.getMainLoopFuture()->wait();
}

glAbs::Destroyer::~Destroyer()
{
    glfwTerminate();
    std::cout << "destructor of destroyer called";
}

glAbs::Destroyer glAbs::init()
{
    //TODO: implement this function to initialize every thing
//    throw "not implemented";

//    if (!glAbs::Window::glfwInitialized)
//    {
//        if (!glfwInit())
//            throw "Failed to initialize GLFW";
//        glAbs::Window::glfwInitialized = true;
//    }

    return glAbs::Destroyer(); //when the main function ends the destructor of Destroyer gets called and glfw get terminated
}