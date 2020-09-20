#pragma once

#include "base.h"
#include "window/window.h"
#include "layers/layer_array.h"
#include "time/timer.h"
#include "input/input.h"
#include "renderer/renderer.h"

#include "SDL2/SDL_timer.h"


namespace Bubble
{
	class Application
	{
		// Just a pointers
		static Window* s_CurrentWindow;
		static std::string* s_CurrentDir;
	protected:
		Timer m_Timer;
		// Resources
		Scope<Window> m_Window;
		LayerArray m_LayerArray;
		std::string m_CurrentDir;
		
	public:
		Application(Window* window = nullptr);
		virtual ~Application() { s_CurrentWindow = nullptr; }

		void Run();

		void PushLayer(Layer* layer);
		void InsertLayer(int id, Layer* layer);
		void RemoveLayer(int id);
		void SwapLayers(int id_1, int id_2);


		// Take path to executable
		void SetCurrentDir(const std::string& path);
		static const std::string& GetCurrentDir();

		static Window* GetWindow();
		static float GetTime() { return SDL_GetTicks() / 1000.0f; }
	};
}