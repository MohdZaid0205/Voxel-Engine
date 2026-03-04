
#include "api.hpp"
#include "application.hpp"
#include "logging.hpp"

namespace Engine {
	ENGINE_API HWND OnInitialize(HWND parentHwnd, int width, int height);
	ENGINE_API void OnShutdown();
	ENGINE_API void OnUpdate();
}