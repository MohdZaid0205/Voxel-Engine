#include "application.hpp"

Engine::Application::Application(String title, u32 w, u32 h) {
	application_window = nullptr;
	application_title = title;
	application_w = w;
	application_h = h;
	application_window_callback = nullptr;
}

Engine::Application& Engine::Application::instance() {
	if (!application)
		application.reset(CreateApplication());
	return *application;
}


Engine::String Engine::Application::get_application_title() {
	return application_title;
}

Engine::u32 Engine::Application::get_application_width() {
	return application_w;
}

Engine::u32 Engine::Application::get_application_height() {
	return application_h;
}

GLFWwindow* Engine::Application::get_application_window() {
	return application_window;
}

Engine::Application::WindowCallbackFunction 
	Engine::Application::get_application_window_callback() {
	return application_window_callback;
}

void Engine::Application::set_application_window(GLFWwindow* window) {
	application_window = window;
}

void Engine::Application::set_application_window_callback(
	Engine::Application::WindowCallbackFunction function
) {
	application_window_callback = function;
}


void Engine::Application::defaultFixedSizeWindowCallback(
	GLFWwindow* window, u32 w, u32 h) {
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, false);;
}

void Engine::Application::defaultResizableWindowCallback(
	GLFWwindow* window, u32 w, u32 h) {
	glViewport(0, 0, w, h);
}


void Engine::Application::defaultNoDefaultWindowCallback(
	GLFWwindow* window, u32 w, u32 h) {
	// DOES NOTHING LOL
}