#pragma once

#include "api.hpp"
#include "application.hpp"
#include "exceptions.hpp"

namespace Engine {

	ENGINE_API void RegisterApplication(Application* (*function)(void));

	namespace Startup {

		namespace Flags {
			extern bool isGlfwInit;
			extern bool isGladInit;
			extern bool isWndwInit;
		};

		Expected<bool> initGlfw();
		Expected<bool> initGlad();
		Expected<bool> initWndw(i32 w, i32 h, String name);

		Attempt::Status FailedToInitializeGlfwException(String reason);
		Attempt::Status FailedToInitializeGladException(String reason);
		Attempt::Status FailedToInitializeWndwException(String reason);
	};

	namespace State {
		extern enum State {
			STATE_PAUSED  = 0b00,
			STATE_RUNNING = 0b01,
			STATE_UNKNOWN = 0b10,
		} current;

		ENGINE_API bool EnginePause();
		ENGINE_API bool EngineRun();
	}

	ENGINE_API bool IsInitialized();
	ENGINE_API HWND OnInitialize(HWND parentHwnd, String name, i32 width, i32 height);
	ENGINE_API void OnEvent(Event* event);
	ENGINE_API void OnUpdate();
	ENGINE_API void OnStandalone();
	ENGINE_API void OnShutdown();
}