#include "events.hpp"
#include <iostream>

void Engine::button_clicked_event_handler(i32 id)
{
	std::cout << "button clicked id: " << id << std::endl;
}