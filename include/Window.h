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
        int hint, * value;

        ~WindowHint();
    };

    struct glfwWindowSettings
    {
        glfwWindowSettings();

        ~glfwWindowSettings();

        glfwWindowSettings(glfwWindowSettings&& settings) noexcept;

        unsigned int dimensions;
        int width;
        int height;
        const char* title;

        int* majorContextVersion;
        int* minorContextVersion;
        std::vector<WindowHint> windowHints;

        GLFWmonitor* monitor;
        GLFWwindow* share;

        bool runMainLoopInParallel;

        GLbitfield clearMask;
        bool callSwapInterval;
        int swapInterval;
        glm::vec4 clearColor;
    };

    class Window
    {
    private:
        static bool glfwInitialized;
        static bool glewInitialized;
        GLFWwindow* glfwWindow;
        std::function<void()> setup;
        std::function<void()> mainloop;
        std::function<void()> callback;
        glfwWindowSettings settings;
        std::future<void> mainLoopFuture;

    public:
        bool showWindow = true;

        Window(std::function<void()> setup, std::function<void()> mainloop, std::function<void()> callback = [] {},
               glfwWindowSettings settings = glfwWindowSettings());

        ~Window();

        void runMainLoop();

        Window(Window&& window) noexcept;

        std::future<void>& getMainLoopFuture() const;
    };
}
#endif //ACGL_ABSTRACTION_WINDOW_H