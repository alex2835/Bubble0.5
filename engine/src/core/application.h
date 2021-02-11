#pragma once

#include "base.h"
#include "core/window.h"
#include "core/layer_array.h"
#include "core/timer.h"
#include "core/input.h"
#include "renderer/renderer.h"

#include "SDL2/SDL_timer.h"


namespace Bubble
{
	struct Application
	{
		Timer mTimer;
		Window mWindow;
		LayerArray mLayerArray;
		
		Application();
		virtual ~Application() {}

		void Run();
		void PushLayer(Layer* layer);
		void InsertLayer(int id, Layer* layer);
		void RemoveLayer(int id);
		void SwapLayers(int id_1, int id_2);
	};
}