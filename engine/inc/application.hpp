#pragma once

#include "api.hpp"
#include "logging.hpp"
#include "events.hpp"
#include "layers.hpp"

namespace Engine {

#pragma region ApplicationDeclaration[s]
	class Application;
	class ApplicationInstanceException;
	class ApplicationCreationException;
#pragma endregion

	// TODO: Maybe treat Application as a SINGLETON among its inheriting classes,
	// TODO: Instance of application is to be created via its Child Classes.
	extern Application* CreateApplication();

	class Application {
	private:
		static Unique<Application> application;		//> SINGLETON instance

	private:
		std::vector<Unique<Event>> application_deferred_events;
		LayerStack application_layer_stack;	//> LAYER STACK to manage different layers
		String application_title;			//> TITLE (name/heading) of window
		u32 application_w;					//> WIDTH of window in number of pixels
		u32 application_h;					//> HEIGHT of window in number of pixels
		GLFWwindow* application_window;		//> GLFW WINDOW

		// user defined function that runs when event::windowResize is triggered.
		// it is not necessary to use this callback, in case of unavailablity of
