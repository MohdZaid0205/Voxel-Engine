#include "engine.hpp"

#include <iostream>

GLFWwindow* screen;

HWND Engine::OnInitialize(HWND parentHwnd, Engine::i32 width, Engine::i32 height) {
    if (!glfwInit()) {
        return NULL;
    }

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* g_Window = glfwCreateWindow(width, height, "Engine Viewport", NULL, NULL);
    HWND glfwHwnd = glfwGetWin32Window(g_Window);

    SetParent(glfwHwnd, parentHwnd);
    LONG style = GetWindowLong(glfwHwnd, GWL_STYLE);
    SetWindowLong(glfwHwnd, GWL_STYLE, (style & ~WS_POPUP) | WS_CHILD | WS_VISIBLE);
    screen = g_Window;
    glfwMakeContextCurrent(g_Window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::cout << "idk what happened" << std::endl;
    return glfwHwnd;
}

void Engine::OnShutdown() {

}

void Engine::OnUpdate() {
    if (!screen) return;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(screen);
    glfwPollEvents();
}