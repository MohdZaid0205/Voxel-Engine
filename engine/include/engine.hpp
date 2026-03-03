
#include "api.hpp"
#include "application.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>

namespace Engine {
	ENGINE_API HWND OnInitialize(HWND parentHwnd, int width, int height);
	ENGINE_API void OnShutdown();
	ENGINE_API void OnUpdate();
}