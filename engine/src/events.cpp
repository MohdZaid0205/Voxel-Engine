#include "events.hpp"

ENGINE_API Engine::WindowClosedEvent* Engine::CreateWindowClosedEvent(){
	return new WindowClosedEvent();
}

ENGINE_API Engine::WindowResizedEvent* Engine::CreateWindowResizedEvent(u32 w, u32 h){
	return new WindowResizedEvent(w, h);
}

ENGINE_API Engine::KeyPressedEvent* Engine::CreateKeyPressedEvent(i32 k, i32 r){
	return new KeyPressedEvent(k, r);
}

ENGINE_API Engine::KeyReleasedEvent* Engine::CreateKeyReleasedEvent(i32 k){
	return new KeyReleasedEvent(k);
}

