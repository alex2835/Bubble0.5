#pragma once

#include "SDL2/SDL_events.h"

#include <string>


namespace Bubble
{
	struct Layer
	{
		std::string m_Name;

		Layer(const std::string& name = "Layer") : m_Name(name) {}
		virtual ~Layer() {};

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(SDL_Event& event) {}
	};
}
