#pragma once

#include "SDL2/SDL_events.h"


namespace Bubble
{
	class Window
	{
	public:
		virtual ~Window() {};

		virtual bool IsOpen() = 0;
		virtual void Close() = 0;

		virtual int GetWindth() = 0;
		virtual int GetHeight() = 0;

		virtual bool PollEvent(SDL_Event& event) = 0;
		virtual void OnEvent(SDL_Event& event) = 0;
		virtual void OnUpdate() = 0;

		virtual void SetVSync(bool mode) = 0;
	};
}