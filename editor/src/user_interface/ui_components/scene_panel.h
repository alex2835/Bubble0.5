#pragma once

#include "engine.h"
#include "imgui.h"

namespace Bubble
{
	struct ScenePanel
	{
		// Skybox
        int SelectedSkyboxIDFirst = 0;
        int SelectedSkyboxIDSecond = 0;
        std::string SelectedSkyboxNameFirst;
        std::string SelectedSkyboxNameSecond;


		void Draw(bool* is_open);
	};
}