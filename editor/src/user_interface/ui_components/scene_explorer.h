#pragma once

#include "engine.h"

#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Bubble
{
	typedef void(*FCustumEntityProperties)(Entity);

	class SceneExplorer
	{
	public:
		Entity SelectedEntity;

		void Draw(bool* is_open_explorer, bool* is_open_properties, Scene* scene);
		void DrawComponents(Entity entity);
	};
}