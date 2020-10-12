#pragma once

#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "scene/scene.h"
#include "scene/components.h"
#include "scene/entity/entity.h"
#include "renderer/light/light.h"

namespace Bubble
{
	typedef void(*FCustumEntityProperties)(Entity);

	class SceneExplorer
	{
	public:
		Entity SelectedEntity;
		// Possible to draw custom property that will be displayed in property panel
		//std::vector<FCustumEntityProperties> CustomEntityProperties;

		void Draw(bool* is_open_explorer, bool* is_open_properties, Scene* scene);

		void DrawComponents(Entity entity);
	};
}