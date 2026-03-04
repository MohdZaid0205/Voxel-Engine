#include "engine.hpp"

#include <iostream>
Engine::Application* app = nullptr;

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
    app = new Application(g_Window);
    glfwMakeContextCurrent(g_Window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::cout << "idk what happened" << std::endl;
    return glfwHwnd;
}

void Engine::OnShutdown() {

}

void Engine::OnUpdate() {
    if (!app) return;
    app->renderFrame();
}