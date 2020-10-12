#pragma once

#include "fstream"
#include "entity_serialization.h"


namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene);

	void OpenProject(const std::string& path, Scene* scene);

}