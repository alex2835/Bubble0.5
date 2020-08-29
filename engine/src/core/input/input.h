#pragma once

#include "glm/glm.hpp"
#include "SDL2/SDL_events.h"

#include "window/window.h"


namespace Bubble
{
	class Input
	{
		static short s_KeyMap[256];
		static int s_MouseKeyMap[16];
		static int s_MouseWheelOffset;

		static int s_MousePosX;
		static int s_MousePosY;
		static int s_MouseRelPosX;
		static int s_MouseRelPosY;

		static SDL_Window* s_Window;

	public:
		static void SetWindow(Window* window) { s_Window = (SDL_Window*)window; }
		static void OnEvent(SDL_Event& event);
		
		// SDLK_a, SDLK_1, ...
		static bool IsKeyPressed(SDL_Keycode code);
		// SDLK_a, SDLK_1, ...
		static bool IsKeyClick(SDL_Keycode code);

		/*
			SDL_BUTTON_LEFT
			SDL_BUTTON_MIDDLE
			SDL_BUTTON_RIGHT
			SDL_BUTTON_X1
			SDL_BUTTON_X2
		*/
		static bool IsMouseButtonPressed(int button);

		static glm::ivec2 GetMousePosition();
		static int GetMouseX();
		static int GetMouseY();

		static glm::ivec2 GetMouseRelPosition();
		static int GetMouseRelX();
		static int GetMouseRelY();

		static glm::vec2 fGetMousePosition();
		static float fGetMouseX();
		static float fGetMouseY();

		static glm::vec2 fGetMouseRelPosition();
		static float fGetMouseRelX();
		static float fGetMouseRelY();

		static int GetMouseWheelOffset();
	};
}