#pragma once

#include "core/window.h"
#include "core/application.h"
#include "glm/glm.hpp"

namespace Bubble
{
	class Input
	{
		Window* mWindow;
		int mKeyMap[256];
		int mMouseKeyMap[16];
		int mMouseKeyMapLast[16];
		int mMouseWheelOffset;

		int mMousePosX;
		int mMousePosY;
		int mMouseRelPosX;
		int mMouseRelPosY;

	public:
		Input(Window* window)
			: mWindow(window)
		{}

		void OnEvent(SDL_Event& event);
		
		// Codes: SDLK_a, SDLK_1, ...
		bool IsKeyPressed(SDL_Keycode code);
		// Codes: SDLK_a, SDLK_1, ...
		bool IsKeyClick(SDL_Keycode code);

		/*
		*	Codes:
			SDL_BUTTON_LEFT
			SDL_BUTTON_MIDDLE
			SDL_BUTTON_RIGHT
			SDL_BUTTON_X1
			SDL_BUTTON_X2
		*/
		bool IsMouseButtonPressed(int button);

		glm::ivec2 GetMousePosition();
		int GetMouseX();
		int GetMouseY();

		glm::ivec2 GetMouseRelPosition();
		int GetMouseRelX();
		int GetMouseRelY();

		// return values between 0.0f and 1.0f
		glm::vec2 fGetMousePosition();
		float fGetMouseX();
		float fGetMouseY();

		glm::vec2 fGetMouseRelPosition();
		float fGetMouseRelX();
		float fGetMouseRelY();

		int GetMouseWheelOffset();

		// Flush all relative information
		void NewFrame();
	};
}