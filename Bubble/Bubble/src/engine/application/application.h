#pragma once

#include "../layers/layer_array.h"
#include "../window/window.h"

namespace Bubble
{
	struct Application
	{
		LayerArray layer_array;
		Window* window;

		Application(Window* window = NULL);
		virtual ~Application();

		void push_layer(Layer* layer);
		void remove_layer(int id);
		void emplace_layer(int id, Layer* layer);
		void swap_layers(int id_1, int id_2);

		void setWindow(Window* window);
		void run();
	};

	Application* create_application();
}