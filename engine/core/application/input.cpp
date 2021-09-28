
#include "input.h"

namespace Bubble
{
	void Input::OnEvent(SDL_Event& event)
	{
		switch (event.type)
		{
			case SDL_KEYUP:
				if (event.key.keysym.sym >= 1073741881) {
					mKeyMap[event.key.keysym.sym - 1073741881] = 0;
				}
				else if (event.key.keysym.sym < 128) {
					mKeyMap[event.key.keysym.sym] = 0;
				}
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym >= 1073741881) {
					mKeyMap[event.key.keysym.sym - 1073741881] = 1 + event.key.repeat;
				}
				else if (event.key.keysym.sym < 128) {
					mKeyMap[event.key.keysym.sym] = 1 + event.key.repeat;
				}
				break;

			case SDL_MOUSEWHEEL:
				mMouseWheelOffset = event.wheel.y;
				break;

			case SDL_MOUSEMOTION:
				mMousePosX = event.motion.x;
				mMousePosY = event.motion.y;
				mMouseRelPosX = event.motion.xrel;
				mMouseRelPosY = event.motion.yrel;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mMouseKeyMap[event.button.button] = event.button.clicks;
				break;

			case SDL_MOUSEBUTTONUP:
				mMouseKeyMap[event.button.button] = 0;
				break;
			}
	}

	bool Input::IsKeyPressed(SDL_Keycode code)
	{
		if (code >= 1073741881) {
			code -= 1073741881;
		}
		return mKeyMap[code];
	}

	bool Input::IsKeyClick(SDL_Keycode code)
	{
		if (code >= 1073741881) {
			code -= 1073741881;
		}
		return mKeyMap[code] == 1;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return mMouseKeyMap[button];
	}

	void Input::SetMousePosition(glm::ivec2 pos)
	{
		SDL_WarpMouseInWindow(mWindow.GetSDLWindow(), pos.x, pos.y);
	}

	glm::ivec2 Input::GetMousePosition()
	{
		return glm::ivec2(mMousePosX, mMousePosY);
	}

	glm::vec2 Input::fGetMousePosition()
	{
		glm::vec2 window_size = mWindow.GetSize();
		return glm::vec2((float)mMousePosX / window_size.x, (float)mMousePosY / window_size.y);
	}

	float Input::fGetMouseX()
	{
		int width = mWindow.GetWidth();
		return (float)mMousePosX / width;
	}

	float Input::fGetMouseY()
	{
		int height = mWindow.GetHeight();
		return (float)mMousePosY / height;
	}

	glm::vec2 Input::fGetMouseRelPosition()
	{
		glm::vec2 window_size = mWindow.GetSize();
		return glm::vec2((float)mMouseRelPosX / window_size.x, (float)mMouseRelPosY / window_size.y);
	}

	float Input::fGetMouseRelX()
	{
		int width = mWindow.GetWidth();
		return (float)mMouseRelPosX / width;
	}

	float Input::fGetMouseRelY()
	{
		int height = mWindow.GetHeight();
		return (float)mMouseRelPosY / height;
	}

	int Input::GetMouseX()
	{
		return mMousePosX;
	}

	int Input::GetMouseY()
	{
		return mMousePosY;
	}

	glm::ivec2 Input::GetMouseRelPosition()
	{
		return glm::ivec2(mMouseRelPosX, mMouseRelPosY);
	}

	int Input::GetMouseRelX()
	{
		return mMouseRelPosX;
	}

	int Input::GetMouseRelY()
	{
		return mMouseRelPosY;
	}

	int Input::GetMouseWheelOffset()
	{
		return mMouseWheelOffset;
	}

    void Input::NewFrame()
    {
        mMouseRelPosX	  = 0.0f;
        mMouseRelPosY	  = 0.0f;
        mMouseWheelOffset = 0.0f;
        memmove(mMouseKeyMapLast, mMouseKeyMap, sizeof(mMouseKeyMap));
    }

}