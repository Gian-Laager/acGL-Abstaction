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
        int hint, value;
    };

    struct glfwWindowSettings
    {
        unsigned int dimensions = 2;
        int width = 640;
        int height = 480;
        const char* title = "title";

        int majorContextVersion = 4;
        int minorContextVersion = 1;
        std::vector<WindowHint> windowHints = {
                WindowHint{GLFW_CONTEXT_VERSION_MAJOR, majorContextVersion},
                WindowHint{GLFW_CONTEXT_VERSION_MINOR, minorContextVersion},
                WindowHint{GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
                WindowHint{GLFW_OPENGL_FORWARD_COMPAT, true}
        };

        GLFWmonitor* monitor = nullptr;
        GLFWwindow* share = nullptr;

        bool runMainLoopInParallel = true;
    };

    class Window
    {
    private:
        GLFWwindow* glfwWindow;
        std::function<void()> mainloop;
        glfwWindowSettings settings;

    public:
        GLbitfield clearMask = GL_COLOR_BUFFER_BIT;

        Window(std::function<void()> mainloop, std::function<void()> callback = []{}, glfwWindowSettings settings = glfwWindowSettings());
    };
}


#endif //ACGL_ABSTRACTION_WINDOW_H
