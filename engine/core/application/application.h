#pragma once

#include "base/base.h"
#include "base/timer.h"
#include "engine/engine.h"
#include "layer_array.h"
#include "SDL2/SDL_timer.h"

namespace Bubble
{
	struct Application
	{
		Engine 	  mEngine;
		Timer      mTimer;
		LayerArray mLayers;

		Application();
		virtual ~Application() {}
		void Run();
		void PushLayer(Layer* layer);
		void InsertLayer(int id, Layer* layer);
		void RemoveLayer(int id);
		void SwapLayers(int id_1, int id_2);
	};
}