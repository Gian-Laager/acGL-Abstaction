//
// Created by Gian Laager on 01.07.20.
//

#ifndef ACGL_ABSTRACTION_WINDOW_H
#define ACGL_ABSTRACTION_WINDOW_H

#include "pch.h"

#define setMainWindowHints() for (auto& windowHint : MainWindowSettings::getInstance()->windowHints)\
                                  glfwWindowHint(windowHint.hint, *windowHint.value);

#define setWindowHints(window) for (auto& windowHint : window->settings.windowHints)\
                                  glfwWindowHint(windowHint.hint, *windowHint.value);

namespace glAbs
{
    struct WindowHint
    {
        WindowHint(int i, std::shared_ptr<int> pInt);

        int hint;
        std::shared_ptr<int> value;

        WindowHint(WindowHint&& hint) noexcept;

        WindowHint(const WindowHint& hint) noexcept;
    };

    struct glfwWindowSettings
    {
        glfwWindowSettings();

        glfwWindowSettings(glfwWindowSettings&& settings) noexcept;

        glfwWindowSettings(const glfwWindowSettings& settings) noexcept;

    private:
        void initWindowHints();

    public:
        unsigned int dimensions;
        int width;
        int height;
        std::string title;

        std::shared_ptr<int> majorContextVersion;
        std::shared_ptr<int> minorContextVersion;
        std::vector<WindowHint> windowHints;

        GLFWmonitor* monitor;
        GLFWwindow* share;

//        bool runMainLoopInParallel;

        bool callSwapInterval;
        int swapInterval;

        GLbitfield clearMask;
        glm::vec4 clearColor;
    };

    class Window
    {
    private:
        void createNewGlfwWindow();

    public:
        static std::mutex glfwMutex;
        std::function<void()> setup;
        std::function<void()> mainloop;
        std::function<void()> callback;
        glfwWindowSettings settings;

    protected:
        GLFWwindow* glfwWindow;
        std::future<void> mainLoopFuture;

    public:
        bool showWindow;

        static void glfwWindowNullptrCheck(GLFWwindow* glfwWindow);

        Window(std::function<void()> mainloop, std::function<void()> setup = [] {},
               std::function<void()> callback = [] {},
               glfwWindowSettings settings = glfwWindowSettings());

        void runMainLoop();

        Window(Window&& window) noexcept;

        const std::future<void>* getMainLoopFuture() const;
    };

    struct MainWindowSettings : public glfwWindowSettings
    {
    private:
        static MainWindowSettings* instance;

        static void createNewMainWindowSettingsInstance();

        MainWindowSettings();

    public:
        static MainWindowSettings* getInstance();

//        std::shared_ptr<int> majorContextVersion;
//        std::shared_ptr<int> minorContextVersion;
//        std::vector<glAbs::WindowHint> windowHints;

        friend glAbs::Destroyer::~Destroyer();
    };

    class MainWindow : public Window
    {
    private:
        static MainWindow* instance;

        static void createNewMainWindowInstance();

        MainWindow();

    public:
        static MainWindow* getInstance();

        friend glAbs::Destroyer::~Destroyer();
    };
}
#endif //ACGL_ABSTRACTION_WINDOW_H