#pragma once

#include "SDL2/SDL_events.h"
#include "glm/glm.hpp"


namespace Bubble
{
	class Window
	{
	public:
		virtual ~Window() {};

		virtual bool IsOpen() = 0;
		virtual void Close() = 0;

		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual glm::ivec2 GetSize() = 0;

		virtual bool PollEvent(SDL_Event& event) = 0;
		virtual void OnEvent(SDL_Event& event) = 0;
		virtual void OnUpdate() = 0;

		virtual void SetVSync(bool mode) = 0;
	};
}