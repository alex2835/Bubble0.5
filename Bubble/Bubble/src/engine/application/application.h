#pragma once

#include "../layers/layer_array.h"
#include "../window/window.h"

namespace Bubble
{
	struct Application
	{
		static Window* s_Window;
		LayerArray m_LayerArray;

		Application(Window* window = NULL);
		virtual ~Application();

		void push_layer(Layer* layer);
		void remove_layer(int id);
		void emplace_layer(int id, Layer* layer);
		void swap_layers(int id_1, int id_2);

		void Run();


		static Window* GetWindow();
		static void SetWindow(Window* window);
	};

	Application* create_application();
}