#pragma once

#include "engine.h"
#include <fstream>

namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene);

	void OpenProject(const std::string& path, Scene* scene);
}