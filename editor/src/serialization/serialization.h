#pragma once

#include "ui.h"
#include "loader.h"
#include "fstream"
#include "entity_serialization.h"
#include "renderer/renderer.h"

namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene, UI* ui);

	void OpenProject(const std::string& path, Scene* scene, UI* ui);
}