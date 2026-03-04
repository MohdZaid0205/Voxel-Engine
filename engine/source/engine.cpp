#include "engine.hpp"

#include <iostream>
Engine::Application* app = nullptr;

HWND Engine::OnInitialize(HWND parentHwnd, Engine::i32 width, Engine::i32 height) {
    if (!glfwInit()) {
        Console::Error<Console::HIG>(
            "Failed to initialize GLFW"_B, 
            "defaulting to =>"_D,"EXIT"_B
        );
        // TODO: implement exit in a way that debug doesnt abruptly stops
        // current behaviour forces window to close as soon as failure is
        // occured within conteext of engine. maybe return NULL and check
        // within EDITOR wether to show gui or to show a warning.
        // exit(-1);    // => causes abrupt exit.
        return NULL;
    }

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* g_Window = glfwCreateWindow(width, height, "Viewport", NULL, NULL);
    app = new Application(g_Window);

    HWND glfwHwnd = glfwGetWin32Window(g_Window);

    SetParent(glfwHwnd, parentHwnd);
    LONG style = GetWindowLong(glfwHwnd, GWL_STYLE);
    SetWindowLong(glfwHwnd, GWL_STYLE, (style & ~WS_POPUP) | WS_CHILD | WS_VISIBLE);
    glfwMakeContextCurrent(g_Window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    return glfwHwnd;
}

void Engine::OnShutdown() {

}

void Engine::OnUpdate() {
    if (!app) return;
    app->renderFrame();
}