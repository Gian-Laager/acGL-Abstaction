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

///Hello world with this Library (see in path/to/acGL-Abstraction/test/basic_window/basic_window.cpp for the full code)
void glAbs::hello_GL()
{
    struct Vertex
    {
        float x, y;
    };

    VertexArray vertexArray(6);
    IndexBuffer indexBuffer;
    Shader shader("../../../res/shaders/basic2dShader.glsl");
    VertexBufferLayout positionLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);;
    RenderSettings renderSettings(vertexArray.numberOfIndices);
//    renderSettings.drawMode = GL_LINES;
    VertexBuffer vertexBuffer;
    VertexArrayRenderer renderer(&vertexArray, &shader, &renderSettings);

    glfwWindowSettings settings;
//    settings.runMainLoopInParallel = true;

    glAbs::MainWindow::getInstance()->setup = [&] {
        const char* versionGL;
        glCall(versionGL = (char*) (glGetString(GL_VERSION)));
        std::cout << "openGl version: " << versionGL << std::endl;

        Vertex vb_data[] = {
                Vertex{-0.5f, -0.5f},
                Vertex{-0.5f, 0.5f},
                Vertex{0.5f, 0.5f},
                Vertex{0.5, -0.5}
        };

        unsigned int indices[] = {
                0, 1, 2,
                0, 2, 3
        };

        vertexBuffer.data(vb_data, sizeof(Vertex) * vertexArray.numberOfIndices, GL_STATIC_DRAW);

        indexBuffer.data(indices, vertexArray.numberOfIndices, GL_STATIC_DRAW);

        vertexArray.push(&vertexBuffer, &positionLayout, 1);
        vertexArray.push(&indexBuffer);
    };

    glAbs::MainWindow::getInstance()->mainloop = [&renderer] {
        renderer.draw();
    };

    glAbs::MainWindow::getInstance()->runMainLoop();

    glAbs::MainWindow::getInstance()->getMainLoopFuture()->wait();
}

glAbs::Destroyer::~Destroyer()
{
    glfwTerminate();
    delete glAbs::MainWindow::getInstance();
    delete glAbs::MainWindowSettings::getInstance();
    glAbs::MainWindowSettings::instance = nullptr;
    glAbs::MainWindow::instance = nullptr;
}

static void initGlfw()
{
    if (!glAbs::glfwInitialized)
    {
        if (!glfwInit())
            throw "Failed to initialize GLFW";
        glAbs::glfwInitialized = true;
    }
}

static void initGlew()
{
    if (!glAbs::glewInitialized)
    {
        glewExperimental = true;
        if (GLEW_OK != glewInit())
            throw "Failed to initialize glew";
        glAbs::glewInitialized = true;
    }
}

glAbs::Destroyer glAbs::init()
{
    initGlfw();

//    setMainWindowHints();

    glAbs::MainWindow::getInstance();

    initGlew();

    return glAbs::Destroyer(); //when the main function ends the destructor of Destroyer gets called and glfw get terminated
}

