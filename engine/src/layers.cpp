#include "layers.hpp"

Engine::LayerStack::~LayerStack() {
	for (Layer* layer : stack) {
		layer->on_detach();
		delete layer;
	}
}

void Engine::LayerStack::PushLayer(Layer* layer) {
	if (layer) {
		stack.emplace(stack.begin() + insertion_index, layer);
		insertion_index++;
		layer->on_attach();
	}
}

void Engine::LayerStack::PushOverlay(Layer* layer) {
	if (layer) {
		stack.push_back(layer);
