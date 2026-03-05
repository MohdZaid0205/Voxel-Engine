#include "application.hpp"

Engine::Unique<Engine::Application>
	Engine::Application::application = nullptr;

Engine::Application::Application(GLFWwindow* window, String title, u32 w, u32 h,
	WindowCallbackFunction window_on_resize_callback_function) {
	if (!application) {
		application_window = window;
		application_title = title;
		application_w = w;
		application_h = h;
		application_window_callback = window_on_resize_callback_function;
	}
	else {
		throw Engine::ApplicationCreationException(
			"Cannot create new instances of application "
			"Only ONE instance of application is allowed"
		);
	}
}

Engine::Application::~Application() {
	// FORMALITY for compilation
}

Engine::Application& Engine::Application::instance() {
	if (!Application::application)
		Application::application.reset(CreateApplication());
	return *Application::application;
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

// TODO: remove setter for title, height and width and cleanup
void Engine::Application::set_application_title(Engine::String new_title) {
	application_title = new_title;
}
void Engine::Application::set_application_height(Engine::u32 new_height) {
	application_h = new_height;
}
void Engine::Application::set_application_widht(Engine::u32 new_width) {
	application_w = new_width;
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