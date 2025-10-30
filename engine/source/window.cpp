#include "window.h"

Engine::Window::Window(uInt32 width, uInt32 height, String title,
		enum WindowCallbackType action) : Window(width,height,title)
{
	switch(action){
		case RESIZABLE:
			__resize_callback = defaultResizableWindowCallback;
			break;
		case FIXEDSIZE:
			__resize_callback = defaultFixedSizeWindowCallback;
			break;
		case NODEFAULT:
			__resize_callback = defaultNoDefaultWindowCallback;
			break;
		default:
			Console::Error<Console::HIG>(
				"Default action handler for window resize is invalid"_D, title,
				"must be properly set from enum ie:"_D, "WindowCallbackType"_B
			);
			break;
	}

	
	glfwSetFramebufferSizeCallback(__window, (GLFWframebuffersizefun)__resize_callback);
}

Engine::Window::~Window() {/** nothing to clean */}

GLFWwindow*	Engine::Window::getHandle(){ return __window; }
String Engine::Window::getTitle (){ return __t; }
uInt32 Engine::Window::getWidth (){ return __w; }
uInt32 Engine::Window::getHeight(){ return __h; }

void Engine::Window::setResizeCallback(void(* callback)(GLFWwindow *,uInt32,uInt32))
{ glfwSetFramebufferSizeCallback(__window, (GLFWframebuffersizefun)__resize_callback); }

void Engine::defaultResizableWindowCallback(GLFWwindow * window,uInt32 width,uInt32 height)
{ glfwMakeContextCurrent(window); glViewport(0,0, width, height); }

void Engine::defaultFixedSizeWindowCallback(GLFWwindow * window,uInt32 width,uInt32 height)
{ glfwSetWindowAttrib(window, GLFW_RESIZABLE, false); }

void Engine::defaultNoDefaultWindowCallback(GLFWwindow * window,uInt32 width,uInt32 height)
{ /** does nothing */ }
