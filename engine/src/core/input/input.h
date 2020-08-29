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

		static bool IsKeyPressed(SDL_Keycode code);
		static bool IsKeyClick(SDL_Keycode code);

		static bool IsMouseButtonPressed(int button);
		static glm::ivec2 GetMousePosition();
		static int GetMouseX();
		static int GetMouseY();
		static glm::vec2 fGetMousePosition();
		static float fGetMouseX();
		static float fGetMouseY();
		static int GetMouseWheelOffset();
	};
}