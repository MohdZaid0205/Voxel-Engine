#include "events.hpp"
#include <iostream>

void Engine::button_clicked_event_handler(i32 id)
{
	Console::Debug<Console::MED>("Event Occurred!"_D, "Button was Clicked"_B, "with"_D, "id="_B, id);
}