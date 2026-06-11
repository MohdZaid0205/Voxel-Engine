#include "layers.hpp"

Engine::LayerStack::~LayerStack() {
	for (Layer* layer : stack) {
		layer->on_detach();
		delete layer;
	}
}

void Engine::LayerStack::PushLayer(Layer* layer) {
