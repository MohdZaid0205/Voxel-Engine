#pragma once

#include "api.hpp"
#include "events.hpp"

namespace Engine {
	
	class Layer {
	private:
		String layer_name;
	public:
		Layer(String name) : layer_name(name) {}
		virtual ~Layer() = default;
	public:
		virtual void on_attach() = 0;
		virtual void on_detach() = 0;
		virtual void on_update() = 0;
		virtual void on_event(Event& e) = 0;
	public:
		inline const String& get_layer_name() const { return layer_name; }
	};

	class LayerStack {
	private:
		std::vector<Layer*> stack;
		u32 insertion_index = 0;
	public:
		LayerStack() = default;
		~LayerStack();
	public:
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
