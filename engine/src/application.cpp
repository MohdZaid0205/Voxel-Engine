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
		application_layer_stack = LayerStack();
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
