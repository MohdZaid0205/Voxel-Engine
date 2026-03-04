#pragma once

#include "api.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>

namespace Engine {
	class Application {
	private:
		GLFWwindow* g_application_window;
	public:
		Application(GLFWwindow* window) : g_application_window(window) {};
		~Application();
	public:
		virtual void renderFrame() {
			if (!g_application_window) return;

			render_color(1.0f, 0.0f, 0.0f);
		}
	public:
		void render_color(f32 r, f32 g, f32 b) {
			glClearColor(r, g, b, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(g_application_window);
			glfwPollEvents();
		}
	};
}