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

    Shader shader("../../../res/shaders/basic2dShader.glsl");
    VertexBufferLayout positionLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);;
    VertexBuffer vertexBuffer;
    Renderer renderer(&vertexBuffer, &positionLayout, 1, &shader);

    glfwWindowSettings settings;
//    settings.runMainLoopInParallel = true;

    mainWindow->setup = [&] {
        const char* versionGL;
        glCall(versionGL = (char*) (glGetString(GL_VERSION)));
        std::cout << "openGl version: " << versionGL << std::endl;

        Vertex vb_data[] = {
                Vertex{0.5f, -0.5f},
                Vertex{-0.5f, -0.5f},
                Vertex{0.0f, 0.5f}
        };

        vertexBuffer.data(vb_data, sizeof(Vertex) * 3, GL_STATIC_DRAW);
    };

    mainWindow->mainloop = [&renderer] {
        renderer.draw(3);
    };

    mainWindow->runMainLoop();

    mainWindow->getMainLoopFuture()->wait();
}

glAbs::Destroyer::~Destroyer()
{
    glfwTerminate();
    delete glAbs::MainWindow::getInstance();
    delete glAbs::MainWindowSettings::getInstance();
    glAbs::MainWindowSettings::instance = nullptr;
    glAbs::MainWindow::instance = nullptr;
}

glAbs::Destroyer glAbs::init()
{
    if (!glAbs::glfwInitialized)
    {
        if (!glfwInit())
            throw "Failed to initialize GLFW";
        glAbs::glfwInitialized = true;
    }

    for (auto& windowHint : glAbs::MainWindowSettings::getInstance()->windowHints)
        glfwWindowHint(windowHint.hint, *windowHint.value);

    mainWindow = glAbs::MainWindow::getInstance();


    if (!glAbs::glewInitialized)
    {
        glewExperimental = true;
        if (GLEW_OK != glewInit())
            throw "Failed to initialize glew";
    }

    return glAbs::Destroyer(); //when the main function ends the destructor of Destroyer gets called and glfw get terminated
}
