#pragma once

#include "api.hpp"
#include "application.hpp"
#include "logging.hpp"

// Temporary solution to testing sandbox
// TODO: Move sandbox into user created project as a starting template
namespace Sandbox {
	class SandboxLayer : public Engine::Layer {
	public:
		SandboxLayer() : Layer("Sandbox Layer") {}
		~SandboxLayer() override {}
	public:
		void on_attach() override {
			Engine::Console::Log("Attached SandboxLayer");
		}

		void on_detach() override {
			Engine::Console::Log("Detached SandboxLayer");
		}

		void on_event(Engine::Event& e) override {
			Engine::EventDispatcher dispatcher(e);

			dispatcher.dispatch<Engine::WindowResizedEvent>(
				std::bind(&SandboxLayer::on_window_resize, this, std::placeholders::_1)
			);
		}

		void on_update() override {
			glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(Engine::Application::instance().get_application_window());
			glfwPollEvents();
		}

		bool on_window_resize(Engine::WindowResizedEvent& e) {
			Engine::Console::Log(
				"resized: h=", e.get_height(),
				"w=", e.get_width()
			);
			return true;
		}
	};

	class SandboxApplication : public Engine::Application {
	public:
		SandboxApplication() : Engine::Application(
			nullptr, "SandBoxApp", 0, 0, Engine::Application::defaultResizableWindowCallback) {
			get_application_layer_stack().PushLayer(new SandboxLayer());
		}

		~SandboxApplication() {
			// Nothing for now
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