#include "engine.hpp"

Engine::Application* (*application_initializer)(void) = nullptr;

bool Engine::Startup::Flags::isGlfwInit = false;
bool Engine::Startup::Flags::isGladInit = false;
bool Engine::Startup::Flags::isWndwInit = false;

ENGINE_API void Engine::RegisterApplication(Engine::Application* (*function)(void)) {
	application_initializer = function;
}

Engine::Expected<bool> Engine::Startup::initGlfw(){
	if (!Flags::isGlfwInit) {
		if (!glfwInit()) {
			return std::unexpected(FailedToInitializeGlfwException(
				"glfwInit() returned value false"_D
			));
		}
		return Flags::isGlfwInit = true;
	}
	return true;
}

Engine::Expected<bool> Engine::Startup::initGlad(){
	if (!Flags::isGladInit && Flags::isWndwInit) {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			return std::unexpected(FailedToInitializeGladException(
				"gladLoadGLLoader(...) returned value false"_D
			));
		}
		return Flags::isGladInit = true;
	}
	else {
		if (!Flags::isWndwInit) {
			return std::unexpected(FailedToInitializeGladException(
				"Flags::isWndwInit is false, no window present"_D
			));
		}
	}
	return true;
}

Engine::Expected<bool> Engine::Startup::initWndw(i32 w, i32 h, String name){
	if (!Flags::isWndwInit) {
		GLFWwindow* window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
		if (!window) {
			return std::unexpected(FailedToInitializeWndwException(
				"glfwCreateWindow(w, h, ...) returned value null"_D
			));
		}
		glfwMakeContextCurrent(window);
		Application::instance().set_application_window(window);
		Application::instance().set_application_title(name);
		Application::instance().set_application_width(w);
		Application::instance().set_application_height(h);
		Application::instance().set_application_window_callback(
			Engine::Application::defaultResizableWindowCallback
		);
		return Flags::isWndwInit = true;
	}
	return true;
}

Engine::Attempt::Status Engine::Startup::FailedToInitializeGlfwException(String reason){
	return Attempt::makeError("FailedToInitializeGlfwException"_B, reason);
}

Engine::Attempt::Status Engine::Startup::FailedToInitializeGladException(String reason){
	return Attempt::makeError("FailedToInitializeGladException"_B, reason);
}

Engine::Attempt::Status Engine::Startup::FailedToInitializeWndwException(String reason){
	return Attempt::makeError("FailedToInitializeWndwException"_B, reason);
}

ENGINE_API bool Engine::IsInitialized(){
	return Startup::Flags::isGlfwInit
		&& Startup::Flags::isGladInit
		&& Startup::Flags::isWndwInit;
}

ENGINE_API HWND Engine::OnInitialize(HWND parentHwnd, Engine::String name, Engine::i32 width, Engine::i32 height){
	
	auto initGlfw = Attempt::to(Startup::initGlfw)
		.does("Initialize GLFW context in memory"_D)
		.pass("Sucessfullt initlitalized GLFW context"_D)
		.fail("Could Not initialize GLFW context"_D)
		.execute("Startup::initGlfw");

