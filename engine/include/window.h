#ifndef VOXEL_ENGINE_WINDOW_H
#define VOXEL_ENGINE_WINDOW_H

#include "common.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

using namespace Common;

namespace Engine {
	
	/*
	* This file contains a wrapper around window or specifically GLFWwindow structure (encapsulated)
	* provided by glfw library, to manage window creation, destruction and other related tasks.
	*/

#pragma region WindowImplementaion
	enum WindowCallbackType {
		RESIZABLE = 0x00,			//> allows window to be resizable by user cations.
		FIXEDSIZE = 0x01,			//> user actions cannot alter size of window.
		NODEFAULT = 0x10,			//> resize the window without any default callback action.
	};

	class Window {
	private:
		GLFWwindow* __window;		//> encapsulated GLFWwindow structure pointer.
		String __t;					//> stores title of window.
		uInt32 __w;					//> stores width of window.
		uInt32 __h;					//> stores height of window.

		// user defined function that runs when event::windowResize is triggered.
		// it is not necessary to use this callback, in case of inavailablity of such function,
		// no default action is taken, unless it is specified to initialize window as resizeable.
		// or any other default behaviour is specified.
		void (*__resize_callback)(GLFWwindow*, uInt32, uInt32);
	public:
		Window(uInt32 width, uInt32 height, String title);
		Window(uInt32 width, uInt32 height, String title, enum WindowCallbackType action);
		~Window();
	public:
		GLFWwindow* getHandle();				//> get GLFWwindow pointer.
		String		getTitle(); 				//> get title of window.
		uInt32		getWidth();					//> get width of window.
		uInt32		getHeight();				//> get height of window.
	public:
		// using `setResizeCallback` overrides any default action specified during window creation.
		void setResizeCallback(void (*callback)(GLFWwindow*,uInt32,uInt32));
	public:
		// function to be overriten by implementation of window and all related work happens in ctx.
		virtual bool run() = 0;
	};
#pragma endregion

#pragma region WindowResizeCallbackDefaultActionsDefinitions
	// default resize callback actions -------------------------------------------------------------------------+
	void defaultResizableWindowCallback(GLFWwindow* window, uInt32 width, uInt32 height);	// allows resizing	|
	void defaultFixedSizeWindowCallback(GLFWwindow* window, uInt32 width, uInt32 height);	// no resizing		|
	void defaultNoDefaultWindowCallback(GLFWwindow* window, uInt32 width, uInt32 height);	// standard behav	|
	// ---------------------------------------------------------------------------------------------------------+
#pragma endregion

}

Engine::Window::Window(uInt32 width,uInt32 height,String title)
{
	__w = width; __h = height; __t = title;
	__window = glfwCreateWindow(__w,__h,__t.c_str(),NULL,NULL);
}

#include "window.inl"

#endif