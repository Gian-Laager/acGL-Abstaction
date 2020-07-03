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

        std::shared_ptr<int> majorContextVersion;
        std::shared_ptr<int> minorContextVersion;
        std::vector<WindowHint> windowHints;

        GLFWmonitor* monitor;
        GLFWwindow* share;

//        bool runMainLoopInParallel;

        GLbitfield clearMask;
        bool callSwapInterval;
        int swapInterval;
        glm::vec4 clearColor;
    };

    class Window
    {
    private:
        std::function<void()> setup;
        std::function<void()> mainloop;
        std::function<void()> callback;
        glfwWindowSettings settings;
        GLFWwindow* glfwWindow;
        std::future<void> mainLoopFuture;

    public:
        static bool glfwInitialized;
        static bool glewInitialized;
        bool showWindow;

        Window(std::function<void()> setup, std::function<void()> mainloop, std::function<void()> callback = [] {},
               glfwWindowSettings settings = glfwWindowSettings());

        void runMainLoop();

        Window(Window&& window) noexcept;

        const std::future<void>* getMainLoopFuture() const;
    };
}
#endif //ACGL_ABSTRACTION_WINDOW_H