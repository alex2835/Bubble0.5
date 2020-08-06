#pragma once

#include "../layers/layer_array.h"
#include "../window/window.h"

namespace Bubble
{
	struct Application
	{
	public:
		Application(Window* window = NULL);
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void InsertLayer(int id, Layer* layer);
		void RemoveLayer(int id);
		void SwapLayers(int id_1, int id_2);

		static Window* GetWindow();
		static void SetWindow(Window* window);

	private:
		static Window* s_Window;
		LayerArray m_LayerArray;
	};

	Application* CreateApplication();
}