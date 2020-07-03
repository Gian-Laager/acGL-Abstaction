//
// Created by Gian Laager on 01.07.20.
//

#ifndef ACGL_ABSTRACTION_WINDOW_H
#define ACGL_ABSTRACTION_WINDOW_H

#include "pch.h"

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

        unsigned int dimensions;
        int width;
        int height;
        std::string title;

//        std::shared_ptr<int> majorContextVersion;
//        std::shared_ptr<int> minorContextVersion;
//        std::vector<WindowHint> windowHints;

        GLFWmonitor* monitor;
        GLFWwindow* share;

//        bool runMainLoopInParallel;

        GLbitfield clearMask;
        glm::vec4 clearColor;
    };

    class Window
    {
    public:
        std::function<void()> setup;
        std::function<void()> mainloop;
        std::function<void()> callback;
        glfwWindowSettings settings;

    protected:
        GLFWwindow* glfwWindow;
        std::future<void> mainLoopFuture;

    public:
        bool showWindow;

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

        MainWindowSettings();

    public:
        static MainWindowSettings* getInstance();

        std::shared_ptr<int> majorContextVersion;
        std::shared_ptr<int> minorContextVersion;
        std::vector<glAbs::WindowHint> windowHints;
        bool callSwapInterval;
        int swapInterval;

        friend glAbs::Destroyer::~Destroyer();
    };

    class MainWindow : public Window
    {
    private:
        static MainWindow* instance;

        MainWindow();

    public:
        static MainWindow* getInstance();

        friend glAbs::Destroyer::~Destroyer();
    };
}
#endif //ACGL_ABSTRACTION_WINDOW_H