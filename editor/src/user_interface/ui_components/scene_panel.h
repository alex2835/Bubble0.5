#pragma once

#include "engine.h"
#include "imgui.h"

namespace Bubble
{
	struct ScenePanel
	{
		// Skybox
		std::string mNames;
		int nSelectedFirts = 0;
		int nSelectedSecond = 0;

		void Draw(bool* is_open);
	};
}