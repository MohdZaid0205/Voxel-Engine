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
