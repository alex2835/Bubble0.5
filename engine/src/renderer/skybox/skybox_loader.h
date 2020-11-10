#pragma once

#include "skybox.h"


namespace Bubble
{
	struct SkyboxLoader
	{
		static std::vector<std::pair<std::string, Ref<Skybox>>> LoadedSkyboxes;

		// Directory with (top.png, bot.png, ...)
		static Ref<Skybox> LoadSeparateFiles(const std::string& dir, const std::string& ext = ".jpg");

		// Single file skybox
		static Ref<Skybox> Load(std::string file);
	};
}