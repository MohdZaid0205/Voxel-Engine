#pragma once

#include "api.hpp"
#include "application.hpp"
#include "logging.hpp"

// Temporary solution to testing sandbox
// TODO: Move sandbox into user created project as a starting template
namespace Sandbox {
	class SimpleGame : public Engine::Application {
	public:
		SimpleGame(GLFWwindow* window, Engine::String title, Engine::u32 w, Engine::u32 h):
			Engine::Application(window, title, w, h, defaultFixedSizeWindowCallback) {}
		~SimpleGame() override { /* nothing for now */ }
	public:
		void run() override {
			glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(instance().get_application_window());
			glfwPollEvents();
		}
	};
}

namespace Engine {
	namespace Flags {
		extern bool is_glfw_initialized;
		extern bool is_glad_initialized;
		extern bool is_window_initialized;
	}

	ENGINE_API bool IsInitialized();
	ENGINE_API HWND OnInitialize(HWND parentHwnd, int width, int height);
	ENGINE_API void OnShutdown();
	ENGINE_API void OnUpdate();
}