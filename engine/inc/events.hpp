#pragma once

#include "api.hpp"
#include "logging.hpp"

namespace Engine {

	enum class EventType {
		None = 0,

		// ... WINDOW EVENTS
		WindowClosed, WindowResized,

		// ... KEY EVENTS
		KeyPressed, KeyReleased,

		// ... MOUSE EVENTS
		MouseButtonClicked,
		MouseButtonReleased,
		MouseMoved, MouseScrolled
	};

	class Event {
	public:
		bool is_handled = false;
	public:
		virtual ~Event() {};
		virtual EventType get_event_type() const = 0;
		virtual String    get_string_type() const = 0;
	};

	// Implemented Envets List (may change its location in future but till then its here)

	class WindowClosedEvent;			// Transmitted when application is closed [X] button
	class WindowResizedEvent;			// Transmitted on every resize request for viewport
	class KeyPressedEvent;				// Transmitted when any key has been pressed
	class KeyReleasedEvent;				// Transmitted when any key has been released
	class MouseButtonClickedEvent;		// Transmitted when any button has been pressed
	class MouseButtonReleasedEvent;		// Transmitted when any button has been released
	class MouseMovedEvent;				// Transmitted when mouse moves
	class MouseScrolledEvent;			// Transmitted when scrollwheel up or down

#pragma region EventEndpointsforUsage
	ENGINE_API WindowClosedEvent*			CreateWindowClosedEvent			();
	ENGINE_API WindowResizedEvent*			CreateWindowResizedEvent		(u32 w, u32 h);
	ENGINE_API KeyPressedEvent*				CreateKeyPressedEvent			(i32 k, i32 r);
	ENGINE_API KeyReleasedEvent*			CreateKeyReleasedEvent			(i32 k);
	ENGINE_API MouseButtonClickedEvent*		CreateMouseButtonClickedEvent	(f32 x, f32 y);
	ENGINE_API MouseButtonReleasedEvent*	CreateMouseButtonReleasedEvent	(f32 x, f32 y);
	ENGINE_API MouseMovedEvent*				CreateMouseMovedEvent			(f32 x, f32 y);
	ENGINE_API MouseScrolledEvent*			CreateMouseScrolledEvent		(f32 x, f32 y);
#pragma endregion

#pragma region EventTypesImplementation

	// just to make life easier
	#define GET_EVENT_TYPE(type) EventType get_event_type() const override { return type; }
	#define GET_STRING_TYPE(type) Engine::String get_string_type() const override { return #type; }
	#define GET_STATIC_TYPE(type) static EventType get_static_type() { return type; }

#pragma region 	Window[...]Events
	class WindowClosedEvent : public Event {
	private:
		// .. (NO DATA REQUIRED)
	public:
		WindowClosedEvent() = default;
		~WindowClosedEvent() override = default;
	public:
		GET_EVENT_TYPE(EventType::WindowClosed);
		GET_STATIC_TYPE(EventType::WindowClosed);
		GET_STRING_TYPE(EventType::WindowClosed);
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
		GET_STRING_TYPE(EventType::WindowResized);
	public:
		u32 get_width() { return width; }
		u32 get_height() { return height; }
	};
#pragma endregion
#pragma region Keyboard[...]Events
	class KeyPressedEvent : public Event {
	private:
		i32 key_code;
		i32 repeat_count;
	public:
		KeyPressedEvent(i32 k, i32 rep) : key_code(k), repeat_count(rep) {}
		~KeyPressedEvent() override = default;
	public:
		GET_EVENT_TYPE(EventType::KeyPressed);
		GET_STATIC_TYPE(EventType::KeyPressed);
		GET_STRING_TYPE(EventType::KeyPressed);
	public:
		i32 get_key_code() { return key_code; }
		i32 ger_repeat_count() { return repeat_count; }
