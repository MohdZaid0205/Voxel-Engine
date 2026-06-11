#include "events.hpp"

ENGINE_API Engine::WindowClosedEvent* Engine::CreateWindowClosedEvent(){
	return new WindowClosedEvent();
}

ENGINE_API Engine::WindowResizedEvent* Engine::CreateWindowResizedEvent(u32 w, u32 h){
	return new WindowResizedEvent(w, h);
}
