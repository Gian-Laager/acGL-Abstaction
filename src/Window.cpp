#include "Window.h"

bool glAbs::Window::glfwInitialized = false;
bool glAbs::Window::glewInitialized = false;

glAbs::Window::Window(std::function<void()> setup, std::function<void()> mainloop, std::function<void()> callback,
                      glfwWindowSettings settings) : setup(std::move(setup)),
                                                     mainloop(std::move(mainloop)),
                                                     callback(std::move(callback)),
                                                     settings(std::move(settings)),
                                                     showWindow(true)
{
    if (!glAbs::Window::glfwInitialized)
    {
        if (!glfwInit())
            throw "Failed to initialize GLFW";
        glfwInitialized = true;
    }

    for (auto& windowHint : this->settings.windowHints)
        glfwWindowHint(windowHint.hint, *windowHint.value);

    glfwWindow =
            glfwCreateWindow(this->settings.width, this->settings.height, &this->settings.title[0],
                             this->settings.monitor, this->settings.share);

    if (!glfwWindow)
    {
        glfwTerminate();
        throw "Failed to create window";
    }

    glfwMakeContextCurrent(glfwWindow);

    if (!glAbs::Window::glewInitialized)
    {
        glewExperimental = true;
        if (GLEW_OK != glewInit())
            throw "Failed to initialize glew";
        glewInitialized = true;
    }

    if (this->settings.callSwapInterval)
        glfwSwapInterval(this->settings.swapInterval);
}

void glAbs::Window::runMainLoop()
{
    if (settings.runMainLoopInParallel)
    {
        mainLoopFuture = std::async(std::launch::async, [&]() {
            glfwMakeContextCurrent(glfwWindow);

            setup();

            while (!glfwWindowShouldClose(glfwWindow) && showWindow)
            {
                glCall(glClearColor(settings.clearColor.x, settings.clearColor.y, settings.clearColor.z,
                                    settings.clearColor.w));
                glCall(glClear(settings.clearMask));

                mainloop();

                glfwSwapBuffers(glfwWindow);
                glfwPollEvents();
            }

            callback();
            glfwTerminate();
        });
    } else
    {
        glfwMakeContextCurrent(glfwWindow);

        setup();

        while (!glfwWindowShouldClose(glfwWindow) && showWindow)
        {
            glCall(glClearColor(settings.clearColor.x, settings.clearColor.y, settings.clearColor.z,
                                settings.clearColor.w));
            glCall(glClear(settings.clearMask));

            mainloop();

            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }

        callback();
        glfwTerminate();
    }
}

glAbs::Window::Window(glAbs::Window&& window) noexcept: setup(std::move(window.setup)),
                                                        mainloop(std::move(window.mainloop)),
                                                        callback(std::move(window.callback)),
                                                        settings(std::move(window.settings))
{
    glfwWindow = window.glfwWindow;
    window.glfwWindow = nullptr;
}

const std::future<void>& glAbs::Window::getMainLoopFuture() const
{
    return (std::future<void>&) mainLoopFuture;
}

glAbs::Window::~Window()
{
    delete glfwWindow;
}

glAbs::glfwWindowSettings::glfwWindowSettings(glAbs::glfwWindowSettings&& settings) noexcept: dimensions(
        settings.dimensions),
                                                                                              width(settings.width),
                                                                                              height(settings.height),
                                                                                              title(std::move(
                                                                                                      settings.title)),
                                                                                              majorContextVersion(
                                                                                                      std::move(
                                                                                                              settings.majorContextVersion)),
                                                                                              minorContextVersion(
                                                                                                      std::move(
                                                                                                              settings.minorContextVersion)),
                                                                                              windowHints(std::move(
                                                                                                      settings.windowHints)),
                                                                                              monitor(std::move(
                                                                                                      settings.monitor)),
                                                                                              share(std::move(
                                                                                                      settings.share)),
                                                                                              runMainLoopInParallel(
                                                                                                      settings.runMainLoopInParallel),
                                                                                              clearMask(
                                                                                                      settings.clearMask),
                                                                                              callSwapInterval(
                                                                                                      settings.callSwapInterval),
                                                                                              swapInterval(
                                                                                                      settings.swapInterval),
                                                                                              clearColor(
                                                                                                      settings.clearColor)
{
}

glAbs::glfwWindowSettings::glfwWindowSettings() : dimensions(2),
                                                  width(640),
                                                  height(480),
                                                  title("title"),
//                                                  majorContextVersion(new int),
//                                                  minorContextVersion(new int),
                                                  windowHints(std::vector<WindowHint>()/*
                                                          WindowHint{GLFW_CONTEXT_VERSION_MAJOR, majorContextVersion},
                                                          WindowHint{GLFW_CONTEXT_VERSION_MINOR, minorContextVersion},
                                                          WindowHint{GLFW_OPENGL_PROFILE,
                                                                     std::make_shared<int>(GLFW_OPENGL_CORE_PROFILE)},
                                                          WindowHint{GLFW_OPENGL_FORWARD_COMPAT, std::make_shared<int>(true)})*/),
                                                  monitor(nullptr),
                                                  share(nullptr),
                                                  runMainLoopInParallel(true),
                                                  clearMask(GL_COLOR_BUFFER_BIT),
                                                  callSwapInterval(true),
                                                  swapInterval(1),
                                                  clearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
{
    majorContextVersion = std::shared_ptr<int>(std::make_shared<int>(4));
    minorContextVersion = std::shared_ptr<int>(std::make_shared<int>(1));
    windowHints.reserve(4);
    windowHints.push_back(WindowHint{GLFW_CONTEXT_VERSION_MAJOR, majorContextVersion});
    windowHints.push_back(WindowHint{GLFW_CONTEXT_VERSION_MINOR, minorContextVersion});
    windowHints.push_back(
            WindowHint{GLFW_OPENGL_PROFILE, std::shared_ptr<int>(std::make_shared<int>(GLFW_OPENGL_CORE_PROFILE))});
    windowHints.push_back(WindowHint{GLFW_OPENGL_FORWARD_COMPAT, std::shared_ptr<int>(std::make_shared<int>(true))});
}

glAbs::glfwWindowSettings::glfwWindowSettings(const glAbs::glfwWindowSettings& settings) noexcept: dimensions(
        settings.dimensions),
                                                                                                   width(settings.width),
                                                                                                   height(settings.height),
                                                                                                   title(settings.title),
                                                                                                   majorContextVersion(
                                                                                                           std::make_shared<int>(
                                                                                                                   *settings.majorContextVersion)),
                                                                                                   minorContextVersion(
                                                                                                           std::make_shared<int>(
                                                                                                                   *settings.minorContextVersion)),
                                                                                                   windowHints(
                                                                                                           settings.windowHints),


)
{
    moni
}

glAbs::WindowHint::WindowHint(glAbs::WindowHint&& hint) noexcept: hint(hint.hint),
                                                                  value(std::move(hint.value)) {}

glAbs::WindowHint::WindowHint(int hint, std::shared_ptr<int> value) : hint(hint),
                                                                      value(std::move(value)) {}
