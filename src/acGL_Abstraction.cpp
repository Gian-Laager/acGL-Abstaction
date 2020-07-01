#include "acGL_Abstraction.h"

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

    GLFWwindow* window;

    if (!glfwInit())
    {
        throw "Failed to initialize GLFW";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Failed to create window";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    glewExperimental = true;
    if (GLEW_OK != glewInit())
    {
        throw "Failed to initialize glew";
    }

    const char *versionGL;
    versionGL = (char *) (glGetString(GL_VERSION));
    std::cout << "openGl version: " << versionGL << std::endl;

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;

    Vertex vb_data[] = {
            Vertex{0.5f, -0.5f},
            Vertex{-0.5f, -0.5f},
            Vertex{0.0f, 0.5f}
    };

    vertexBuffer.data(vb_data, sizeof(Vertex) * 3, GL_STATIC_DRAW);

    VertexBufferLayout positionLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);

//    vertexArray.push(&vertexBuffer, &positionLayout, 1);

    Shader shader("../../../res/shaders/basic2dShader.glsl");

    Renderer renderer(&vertexBuffer, &positionLayout, 1, &shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        renderer.draw(3, GL_TRIANGLES);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
