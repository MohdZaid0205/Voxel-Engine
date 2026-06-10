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
}


Engine::LayerStack& Engine::Application::get_application_layer_stack()
{
	return application_layer_stack;
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
