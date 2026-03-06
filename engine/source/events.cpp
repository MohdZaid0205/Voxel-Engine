#include "events.hpp"
#include <iostream>

Engine::LayerStack::~LayerStack(){
	for (Layer* layer : stack) {
		layer->on_detach();
		delete layer;
	}
}

void Engine::LayerStack::PushLayer(Layer* layer){
	if (layer) {
		stack.emplace(stack.begin() + insertion_index, layer);
		insertion_index++;
		layer->on_attach();
	}
}

void Engine::LayerStack::PushOverlay(Layer* layer){
	if (layer) {
		stack.push_back(layer);
		layer->on_attach();
	}
}

void Engine::LayerStack::PopLayer(Layer* layer){
	auto it = std::find(stack.begin(), stack.begin() + insertion_index, layer);
	if (it != stack.begin() + insertion_index) {
		layer->on_detach();
		stack.erase(it);
		insertion_index--;
	}
}

void Engine::LayerStack::PopOverlay(Layer* layer) {
	auto it = std::find(stack.begin() + insertion_index, stack.end(), layer);
	if (it != stack.end()) {
		layer->on_detach();
		stack.erase(it);
	}
}

