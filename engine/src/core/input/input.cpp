
#include "input.h"


namespace Bubble
{
	short Input::s_KeyMap[256];
	int Input::s_MouseKeyMap[16];
	int Input::s_MouseWheelOffset;

	int Input::s_MousePosX;
	int Input::s_MousePosY;
	int Input::s_MouseRelPosX;
	int Input::s_MouseRelPosY;

	void Input::OnEvent(SDL_Event& event)
	{
		switch (event.type)
		{
			case SDL_KEYUP:
				s_KeyMap[event.key.keysym.sym] = 0;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym < 128)
					s_KeyMap[event.key.keysym.sym] = 1 + event.key.repeat;
				break;

			case SDL_MOUSEWHEEL:
				s_MouseWheelOffset = event.wheel.y;
				break;


			case SDL_MOUSEMOTION:
				s_MousePosX = event.motion.x;
				s_MousePosY = event.motion.y;
				s_MouseRelPosX = event.motion.xrel;
				s_MouseRelPosY = event.motion.yrel;
				break;

			case SDL_MOUSEBUTTONDOWN:
				s_MouseKeyMap[event.button.button] = event.button.clicks;
				break;

			case SDL_MOUSEBUTTONUP:
				s_MouseKeyMap[event.button.button] = 0;
				break;
			}
		
	}

	bool Input::IsKeyPressed(SDL_Keycode code)
	{
		return s_KeyMap[code];
	}

	bool Input::IsKeyClick(SDL_Keycode code)
	{
		return s_KeyMap[code] == 1;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return s_MouseKeyMap[button];
	}

	glm::ivec2 Input::GetMousePosition()
	{
		return glm::ivec2(s_MousePosX, s_MousePosY);
	}

	glm::vec2 Input::fGetMousePosition()
	{
		glm::vec2 window_size = Application::GetWindow()->GetSize();
		return glm::vec2((float)s_MousePosX / window_size.x, (float)s_MousePosY / window_size.y);
	}

	float Input::fGetMouseX()
	{
		int width = Application::GetWindow()->GetWidth();
		return (float)s_MousePosX / width;
	}

	float Input::fGetMouseY()
	{
		int height = Application::GetWindow()->GetHeight();
		return (float)s_MousePosY / height;
	}

	glm::vec2 Input::fGetMouseRelPosition()
	{
		glm::vec2 window_size = Application::GetWindow()->GetSize();
		return glm::vec2((float)s_MouseRelPosX / window_size.x, (float)s_MouseRelPosY / window_size.y);
	}

	float Input::fGetMouseRelX()
	{
		int width = Application::GetWindow()->GetWidth();
		return (float)s_MouseRelPosX / width;
	}

	float Input::fGetMouseRelY()
	{
		int height = Application::GetWindow()->GetHeight();
		return (float)s_MouseRelPosY / height;
	}

	int Input::GetMouseX()
	{
		return s_MousePosX;
	}

	int Input::GetMouseY()
	{
		return s_MousePosY;
	}

	glm::ivec2 Input::GetMouseRelPosition()
	{
		return glm::ivec2(s_MouseRelPosX, s_MouseRelPosY);
	}

	int Input::GetMouseRelX()
	{
		return s_MouseRelPosX;
	}

	int Input::GetMouseRelY()
	{
		return s_MouseRelPosY;
	}

	int Input::GetMouseWheelOffset()
	{
		int temp = s_MouseWheelOffset;
		s_MouseWheelOffset = 0;
		return temp;
	}

	void Input::NewFrame()
	{
		Input::s_MouseRelPosX = 0.0f;
		Input::s_MouseRelPosY = 0.0f;
	}

}