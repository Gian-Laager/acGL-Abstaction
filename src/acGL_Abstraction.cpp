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

//    GLFWwindow* window;
//
//    if (!glfwInit())
//    {
//        throw "Failed to initialize GLFW";
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        throw "Failed to create window";
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1);
//
//
//    glewExperimental = true;
//    if (GLEW_OK != glewInit())
//    {
//        throw "Failed to initialize glew";
//    }

//    VertexArray* vertexArray;
    Shader* shader;
    Renderer* renderer;
    VertexBufferLayout* positionLayout;
    VertexBuffer* vertexBuffer;

    glfwWindowSettings settings;
    settings.runMainLoopInParallel = false;

    Window window([&]() {
        const char* versionGL;
        glCall(versionGL = (char*) (glGetString(GL_VERSION)));
        std::cout << "openGl version: " << versionGL << std::endl;

//        vertexArray = new VertexArray();
        vertexBuffer = new VertexBuffer();

        Vertex vb_data[] = {
                Vertex{0.5f, -0.5f},
                Vertex{-0.5f, -0.5f},
                Vertex{0.0f, 0.5f}
        };

        vertexBuffer->data(vb_data, sizeof(Vertex) * 3, GL_STATIC_DRAW);

        positionLayout = new VertexBufferLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);

//        vertexArray->push(&vertexBuffer, &positionLayout, 1);

        shader = new Shader("../../../res/shaders/basic2dShader.glsl");

        renderer = new Renderer(vertexBuffer, positionLayout, 1, shader);
    }, [&]() {
        renderer->draw(3);
    }, []() { std::cout << "mainloop finished" << std::endl; }, settings);

    window.runMainLoop();

    window.getMainLoopFuture().wait();

//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//
//        renderer.draw(3, GL_TRIANGLES);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
}

void init()
{
    //TODO: implement this function to initialize every thing
    throw "not implemented";
}