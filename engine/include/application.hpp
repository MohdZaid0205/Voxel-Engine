#pragma once

#include "api.hpp"
#include "logging.hpp"
#include "events.hpp"

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
		// such function, no default action is taken, unless it is specified to 
		// initialize window as resizeable. or any other default behaviour is specified.
		using WindowCallbackFunction = void (*)(GLFWwindow*, u32, u32);

		enum WindowCallbackType {
			RESIZABLE = 0x00,		//> allows window to be resizable by user cations.
			FIXEDSIZE = 0x01,		//> user actions cannot alter size of window.
			NODEFAULT = 0x10,		//> resize the window without any default callback.
		};							//> REDUNDANT (as of now)

		WindowCallbackFunction application_window_callback;
	
	protected:
		Application(GLFWwindow* window, String title, u32 w, u32 h,
			WindowCallbackFunction window_on_resize_callback_function);
	public:
		virtual ~Application() = 0;

		// I'am aware that using instance(...) for both creation and retreival is bad but
		// here i am doing this and no one can stop me;

		static Application& instance();

		// [DEPRICATED]
		// Application& instance(GLFWwindow* window, String title, u32 w, u32 h);
		// Application& instance(GLFWwindow* window, String title, u32 w, u32 h,
		//	  WindowCallbackFunction window_on_resize_callback_function);

	public:
		
		// all valid getters for private attributes belonging to Application
		
		LayerStack& get_application_layer_stack();
		String get_application_title();
		u32 get_application_height();
		u32 get_application_width();
		GLFWwindow* get_application_window();
		WindowCallbackFunction get_application_window_callback();

	public:
		void run();					// most important function that runs for each frame
		void on_event(Event& e);
		void queue_event(Unique<Event> e);

	public:
		// all valid setters for private attributes belonging to Application

		// void set_application_layer_stack(LayerStack stack);
		void set_application_title(String new_title);
		void set_application_height(u32 new_height);		// only through callbacks
		void set_application_widht(u32 new_width);			// only through callbacks
		void set_application_window(GLFWwindow* window);
		void set_application_window_callback(WindowCallbackFunction function);

	public:
		// GLFW WINDOW API encapsulation
		// NOTE: directly add more functionalities as per usage here!
		// NOTE: use camel case here to differentiate GLFW functionalities from core
		// NOTE: sort functions alphabetically

		bool isOpen() { return !glfwWindowShouldClose(application_window); }
		void makeContextCurrent() { glfwMakeContextCurrent(application_window); }
		void swapBufferes() { glfwSwapBuffers(application_window); }
		void pollEvents() { glfwPollEvents(); }
	
	public:
		// set of predefined functions for default resize callback

		static void defaultResizableWindowCallback(GLFWwindow* window, u32 w, u32 h);
		static void defaultFixedSizeWindowCallback(GLFWwindow* window, u32 w, u32 h);
		static void defaultNoDefaultWindowCallback(GLFWwindow* window, u32 w, u32 h);
	};

	#pragma region ApplicationException[s]
		class ApplicationInstanceException : public std::exception {
		private:
			String message;
		public:
			ApplicationInstanceException(String msg) : message(msg) {}
		public:
			const char* what() const noexcept override {
				return message.c_str();
			}
		};

		class ApplicationCreationException : public std::exception {
		private:
			String message;
		public:
			ApplicationCreationException(String msg) : message(msg) {}
		public:
			const char* what() const noexcept override {
				return message.c_str();
			}
		};
	#pragma endregion
}