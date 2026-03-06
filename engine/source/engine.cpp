#include "engine.hpp"

#include <iostream>


// Some required information
bool Engine::Flags::is_glfw_initialized     = false;
bool Engine::Flags::is_glad_initialized     = false;
bool Engine::Flags::is_window_initialized   = false;

// Function (temporarily present here)
// Supposed to be within auto generated api for user application
Engine::Application* Engine::CreateApplication() {
    return new Sandbox::SandboxApplication();
}

// main engine contents

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
    
    Engine::Flags::is_glfw_initialized = true;
    Console::Info<Console::HIG>("GLFW has been initialized."_B);

    GLFWwindow* g_Window = glfwCreateWindow(width, height, "Viewport", NULL, NULL);
    Engine::Flags::is_window_initialized = true;

    // TODO: make CreateApplication In a Manner that it accepts all required args
    Application::instance().set_application_window(g_Window);
    Application::instance().set_application_title("Viewport");
    Application::instance().set_application_height(height);
    Application::instance().set_application_widht(width);

    Console::Info<Console::HIG>("Applciation instantiated sucessfully."_B);
    Console::Debug<Console::HIG>("Window creation returned =>"_D, g_Window);

    HWND glfwHwnd = glfwGetWin32Window(g_Window);
    SetParent(glfwHwnd, parentHwnd);
    LONG style = GetWindowLong(glfwHwnd, GWL_STYLE);
    
    SetWindowLong(
        glfwHwnd, GWL_STYLE, 
            (style & ~WS_POPUP) | 
            WS_CHILD | 
            WS_VISIBLE
    );
    
    Application::instance().makeContextCurrent();
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Engine::Flags::is_glad_initialized = true;
    Console::Info<Console::HIG>("GLAD has been initilized."_B);

    Console::Debug<Console::HIG>("OnInitialize Routine for ENGINE completed."_D);
    Console::Debug<Console::HIG>("OnInit returned with"_D, "HWND*="_B, glfwHwnd);

    return glfwHwnd;
}

void Engine::OnShutdown() {

}

bool Engine::IsInitialized() {
    return (
        Engine::Flags::is_glfw_initialized &&
        Engine::Flags::is_glad_initialized &&
        Engine::Flags::is_window_initialized
    );
}

void Engine::OnUpdate() {
    if (!IsInitialized())
        return;
    Application::instance().run();
}