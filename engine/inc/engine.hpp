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
