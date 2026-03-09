#include "engine.hpp"

#include <iostream>


// Some required information
bool Engine::Startup::Flags::is_glfw_initialized     = false;
bool Engine::Startup::Flags::is_glad_initialized     = false;
bool Engine::Startup::Flags::is_window_initialized   = false;

// Function (temporarily present here)
// Supposed to be within auto generated api for user application
Engine::Application* Engine::CreateApplication() {
    return new Sandbox::SandboxApplication();
}

// main engine contents

Engine::Attempt::Status Engine::Startup::init_glfw(){
    if (!glfwInit())
        return Engine::Attempt::Status::FAIL;
    Engine::Startup::Flags::is_glfw_initialized = true;
    return Engine::Attempt::Status::PASS;
}

Engine::Attempt::Status Engine::Startup::init_glad(){
    Application::instance().makeContextCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return Engine::Attempt::Status::FAIL;
    Engine::Startup::Flags::is_glad_initialized = true;
    return Engine::Attempt::Status::PASS;
}

#ifndef VOXEL_GAME_DISTRIBUTION

    bool Engine::IsInitialized() {
        return (
            Engine::Startup::Flags::is_glfw_initialized &&
            Engine::Startup::Flags::is_glad_initialized &&
            Engine::Startup::Flags::is_window_initialized
            );
    }

    HWND Engine::OnInitialize(HWND parentHwnd, Engine::i32 width, Engine::i32 height) {
        Engine::Attempt::to<HIG>(Engine::Startup::init_glfw)
            .does("Initialize GLFW"_B, "Load GLFW function[s] at runtime"_D)
            .pass("Loaded required GLFW functions"_D, "init_glfw => PASS"_B)
            .fail("Failed to load GLFW functions"_B , "init_glfw => FAIL"_B);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

        Engine::Attempt::to<HIG>([width, height]() {
            GLFWwindow* window = glfwCreateWindow(width, height, "Editor Viewport", NULL, NULL);
            if (!window)
                return Engine::Attempt::Status::FAIL;
            Engine::Startup::Flags::is_window_initialized = true;

            // TODO: make CreateApplication In a Manner that it accepts all required args 
            Application::instance().set_application_window(window);
            Application::instance().set_application_title("Editor Viewport");
            Application::instance().set_application_height(height);
            Application::instance().set_application_widht(width);

            return Engine::Attempt::Status::PASS;
        })
            .does("Create GLFWwindow"_B, "Captured by WPF as viewport"_D)
            .pass("GLFWwindow insitailization completed"_D,
                "WINDOW =", Application::instance().get_application_window())
            .fail("GLFWwindow creation failed"_B, "glfwCreateWindow => NULL");

        // Some important stuff for wpf caputre process (idk why i need this)
        HWND glfwHwnd = glfwGetWin32Window(
            Engine::Application::instance().get_application_window());
        SetParent(glfwHwnd, parentHwnd);
        LONG style = GetWindowLong(glfwHwnd, GWL_STYLE);
        SetWindowLong(
            glfwHwnd, GWL_STYLE, 
                (style & ~WS_POPUP) | 
                WS_CHILD | 
                WS_VISIBLE
        );
    
        Engine::Attempt::to<HIG>(Engine::Startup::init_glad)
            .does("Initialize GLAD"_B, "Load GLAD function[s] at runtime"_D)
            .pass("Loaded required GLAD functions"_D, "init_glad => PASS"_B)
            .fail("Failed to load GLAD functions"_B, "init_glad => FAIL"_B);

        return glfwHwnd;
    }

    void Engine::OnShutdown() {

    }

    void Engine::OnUpdate() {
        if (!IsInitialized())
            return;
        Application::instance().run();
    }

    void Engine::onEditorButtonClicked(id32 button_id){
        // assuming instant event rather than deferred
        Engine::Event* e = new Engine::EditorButtonClickedEvent(button_id);
        Engine::Application::instance().on_event(*e);
    }

#else

#endif