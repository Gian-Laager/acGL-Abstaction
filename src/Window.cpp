#include "Window.h"

std::mutex glAbs::Window::glfwMutex;

glAbs::Window::Window(std::function<void()> mainloop, std::function<void()> setup, std::function<void()> callback,
                      glAbs::glfwWindowSettings settings) : setup(std::move(setup)),
                                                            mainloop(std::move(mainloop)),
                                                            callback(std::move(callback)),
                                                            settings(std::move(settings)),
                                                            glfwWindow(nullptr),
                                                            showWindow(true)
{

    glfwWindow = glfwCreateWindow(this->settings.width, this->settings.height, &this->settings.title[0],
                                  this->settings.monitor, this->settings.share);

    if (!glfwWindow)
    {
        glfwTerminate();
        throw "Failed to create window";
    }

    glfwMakeContextCurrent(glfwWindow);
}

void glAbs::Window::runMainLoop()
{
    //TODO: Implement this if statement to run the main loop in parallel
//    if (settings.runMainLoopInParallel)
//    {
//        glfwMakeContextCurrent(nullptr);
//        mainLoopFuture = std::async(std::launch::async, [&]() {
//            bool first = true;
//            glfwMutex.lock();
//            glfwMakeContextCurrent(this->glfwWindow);
//            glfwShowWindow(this->glfwWindow);
//
//            this->setup();
//
//            while (!glfwWindowShouldClose(this->glfwWindow) && this->showWindow)
//            {
//                if (!first)
//                    glfwMutex.lock();
//
//                glfwMakeContextCurrent(this->glfwWindow);
//
//
//                std::cout << "this = " << this << std::endl
//                << "this->glfwWindow = " << this->glfwWindow << std::endl;
//                glCall(glClearColor(this->settings.clearColor.x, this->settings.clearColor.y, this->settings.clearColor.z,
//                                    this->settings.clearColor.w));
//                glCall(glClear(this->settings.clearMask));
//
//                this->mainloop();
//
//                glfwSwapBuffers(this->glfwWindow);
//
//                glfwMakeContextCurrent(nullptr);
//
//                glfwMutex.unlock();
////                std::cout << "end of main loop" << std::endl;
//                first = false;
//            }
//
//            callback();
//        });
//    } else
//    {
    mainLoopFuture = std::async(std::launch::async, []() {});
    glfwMakeContextCurrent(glfwWindow);

    setup();

    glfwShowWindow(glfwWindow);

    while (!glfwWindowShouldClose(glfwWindow) && showWindow)
    {
        glfwMutex.lock();
        glfwMakeContextCurrent(glfwWindow);
//            std::cout << "main loop started" << std::endl;
        glCall(glClearColor(settings.clearColor.x, settings.clearColor.y, settings.clearColor.z,
                            settings.clearColor.w));
        glCall(glClear(settings.clearMask));

        mainloop();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
        glfwMakeContextCurrent(nullptr);
        glfwMutex.unlock();
//            std::cout << "end of main loop" << std::endl;
    }

    callback();
//    }
}

glAbs::Window::Window(glAbs::Window&& window) noexcept: setup(std::move(window.setup)),
                                                        mainloop(std::move(window.mainloop)),
                                                        callback(std::move(window.callback)),
                                                        settings(std::move(window.settings)),
                                                        showWindow(window.showWindow) {}

const std::future<void>* glAbs::Window::getMainLoopFuture() const
{
    return &mainLoopFuture;
}

glAbs::glfwWindowSettings::glfwWindowSettings(glAbs::glfwWindowSettings&& settings) noexcept: dimensions(
        settings.dimensions),
                                                                                              width(settings.width),
                                                                                              height(settings.height),
                                                                                              title(std::move(
                                                                                                      settings.title)),
//                                                                                              runMainLoopInParallel(
//                                                                                                      settings.runMainLoopInParallel),
                                                                                              clearMask(
                                                                                                      settings.clearMask),
                                                                                              clearColor(
                                                                                                      settings.clearColor)
{
    monitor = settings.monitor;
    settings.monitor = nullptr;
    share = settings.share;
    settings.share = nullptr;
}

glAbs::glfwWindowSettings::glfwWindowSettings() : dimensions(2),
                                                  width(640),
                                                  height(480),
                                                  title("title"),
                                                  monitor(nullptr),
                                                  share(nullptr),
//                                                  runMainLoopInParallel(true),
                                                  clearMask(GL_COLOR_BUFFER_BIT),
                                                  clearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {}

glAbs::glfwWindowSettings::glfwWindowSettings(const glAbs::glfwWindowSettings& settings) noexcept: dimensions(
        settings.dimensions),
                                                                                                   width(settings.width),
                                                                                                   height(settings.height),
                                                                                                   title(settings.title),
                                                                                                   share(settings.share),
//                                                                                                   runMainLoopInParallel(
//                                                                                                           settings.runMainLoopInParallel),
                                                                                                   clearMask(
                                                                                                           settings.clearMask),
                                                                                                   clearColor(
                                                                                                           settings.clearColor) {}


glAbs::WindowHint::WindowHint(glAbs::WindowHint&& hint) noexcept: hint(hint.hint),
                                                                  value(std::move(hint.value)) {}

glAbs::WindowHint::WindowHint(int hint, std::shared_ptr<int> value) : hint(hint),
                                                                      value(std::move(value)) {}

glAbs::WindowHint::WindowHint(const glAbs::WindowHint& hint) noexcept: hint(hint.hint),
                                                                       value(std::make_shared<int>(*hint.value)) {}


glAbs::MainWindowSettings* glAbs::MainWindowSettings::instance = nullptr;

glAbs::MainWindowSettings::MainWindowSettings()
        : glfwWindowSettings(),
          windowHints(std::vector<WindowHint>()),
          callSwapInterval(true),
          swapInterval(1)
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

glAbs::MainWindowSettings* glAbs::MainWindowSettings::getInstance()
{
    if (instance == nullptr)
        instance = new MainWindowSettings();
    return instance;
}

glAbs::MainWindow* glAbs::MainWindow::instance = nullptr;

glAbs::MainWindow::MainWindow() : Window([]() {}, []() {}, []() {}, *glAbs::MainWindowSettings::getInstance())
{
    glfwMakeContextCurrent(glfwWindow);

    if (glAbs::MainWindowSettings::getInstance()->callSwapInterval)
        glfwSwapInterval(glAbs::MainWindowSettings::getInstance()->swapInterval);
}

glAbs::MainWindow* glAbs::MainWindow::getInstance()
{
    if (instance == nullptr)
        instance = new MainWindow();
    return instance;
}