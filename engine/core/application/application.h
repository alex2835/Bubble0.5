#pragma once

#include "base/base.h"
#include "base/timer.h"
#include "application/window.h"
#include "application/input.h"
#include "application/layer_array.h"
#include "SDL2/SDL_timer.h"

namespace Bubble
{
	struct Application
	{
		Window     mWindow;
        Input	   mInput;
		Timer      mTimer;
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