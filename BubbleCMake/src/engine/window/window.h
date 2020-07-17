#pragma once

//#include "pch.h"
#include "SDL2/SDL.h"


namespace Bubble
{
	struct Window
	{
		virtual ~Window() {};

		virtual bool isOpen() = 0;
		virtual void Close() = 0;

		virtual int GetWindth() = 0;
		virtual int GetHeight() = 0;

		virtual bool PollEvent(SDL_Event& event) = 0;
		virtual void OnEvent(SDL_Event& event) = 0;
		virtual void OnUpdate() = 0;
	};
}