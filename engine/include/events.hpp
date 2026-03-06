#pragma once

#include "api.hpp"
#include "logging.hpp"

namespace Engine {
	
	enum class EventType {
		None= 0,

		// ... WINDOW EVENTS
		WindowClosed, WindowResized,

		// ... KEY EVENTS
		KeyPressed,  KeyReleased,

		// ... MOUSE EVENTS
		MouseButtonPressed, 
		MouseButtonReleased, 
		MouseMoved, MouseScrolled
	};

	class Event {
	public:
		bool is_handled = false;
	public:
		virtual ~Event() = 0;
		virtual EventType get_event_type() const = 0;
	};

	// Implemented Envets List (may change its location in future but till then its here)

	class WindowClosedEvent;			// Transmitted when application is closed [X] button
	class WindowResizedEvent;			// Transmitted on every resize request for viewport
	class KeyPressedEvent;				// Transmitted when any key has been pressed
	class KeyReleasedEvent;				// Transmitted when any key has been released
	class MouseButtonPressedEvent;		// Transmitted when any button has been pressed
	class MouseButtonReleasedEvent;		// Transmitted when any button has been released
	class MouseMovedEvent;				// Transmitted when mouse moves
	class MouseScrolledEvent;			// Transmitted when scrollwheel up or down

	#pragma region EventTypesImplementation

	// just to make life easier
	#define GET_EVENT_TYPE(type) EventType get_event_type() const override { return type; }
	#define GET_STATIC_TYPE(type) static EventType get_static_type() { return type; }

		#pragma region 	Window[...]Events
			class WindowClosedEvent: public Event{
			private:
				// .. (NO DATA REQUIRED)
			public:
				WindowClosedEvent() = default;
				~WindowClosedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::WindowClosed);
				GET_STATIC_TYPE(EventType::WindowClosed);
			};

			class WindowResizedEvent : public Event {
			private:
				u32 width;
				u32 height;
			public:
				WindowResizedEvent(u32 w, u32 h) : width(w), height(h) {}
				~WindowResizedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::WindowResized);
				GET_STATIC_TYPE(EventType::WindowResized);
			public:
				u32 get_width() { return width; }
				u32 get_height() { return height; }
			};
		#pragma endregion
		#pragma region Keyboard[...]Events
			class KeyPreseedEvent : public Event {
			private:
				i32 key_code;
				i32 repeat_count;
			public:
				KeyPreseedEvent(i32 k, i32 rep) : key_code(k), repeat_count(rep) {}
				~KeyPreseedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::KeyPressed);
				GET_STATIC_TYPE(EventType::KeyPressed);
			public:
				i32 get_key_code() { return key_code; }
				i32 ger_repeat_count() { return repeat_count; }
			};

			class KeyReleasedEvent : public Event {
			private:
				i32 key_code;
			public:
				KeyReleasedEvent(i32 k) : key_code(k) {}
				~KeyReleasedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::KeyReleased);
				GET_STATIC_TYPE(EventType::KeyReleased);
			public:
				i32 get_key_code() { return key_code; }
			};
		#pragma endregion
		#pragma region Mouse[...]Events
			class MouseButtonClickedEvent : public Event {
			private:
				i32 button;
			public:
				MouseButtonClickedEvent(i32 b) : button(b) {}
				~MouseButtonClickedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::MouseButtonPressed);
				GET_STATIC_TYPE(EventType::MouseButtonPressed);
			public:
				i32 get_button() { return button; }
			};

			class MouseButtonReleasedEvent : public Event {
			private:
				i32 button;
			public:
				MouseButtonReleasedEvent(i32 b) : button(b) {}
				~MouseButtonReleasedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::MouseButtonReleased);
				GET_STATIC_TYPE(EventType::MouseButtonReleased);
			public:
				i32 get_button() { return button; }
			};

			class MouseMovedEvent : public Event {
			private:
				f32 x_position;
				f32 y_position;
			public:
				MouseMovedEvent(f32 x, f32 y) : x_position(x), y_position(y) {}
				~MouseMovedEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::MouseMoved);
				GET_STATIC_TYPE(EventType::MouseMoved);
			public:
				f32 get_x_position() { return x_position; }
				f32 get_y_position() { return y_position; }
			};

			class MouseScrolledEvent : public Event {
			private:
				f32 x_offset;
				f32 y_offset;
			public:
				MouseScrolledEvent(f32 x, f32 y) : x_offset(x), y_offset(y) {}
				~MouseScrolledEvent() override = default;
			public:
				GET_EVENT_TYPE(EventType::MouseScrolled);
				GET_STATIC_TYPE(EventType::MouseScrolled);
			public:
				f32 get_x_position() { return x_offset; }
				f32 get_y_position() { return y_offset; }
			};
		#pragma endregion

	#pragma endregion

	class EventLayer {

	};
}