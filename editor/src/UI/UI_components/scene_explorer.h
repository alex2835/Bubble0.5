#pragma once

#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "scene/scene.h"
#include "scene/components/basic_components.h"
#include "scene/entity/entity.h"


namespace Bubble
{
	typedef void(*FCustumEntityProperties)(Entity);

	class SceneExplorerPanel
	{
	public:
		Entity SelectedEntity;
		// Possible to draw custom property that will be displayed in property panel
		std::vector<FCustumEntityProperties> CustomEntityProperties;

		void DrawEntitiesExplorer(bool* is_open_explorer, bool* is_open_properties, Scene* scene);

		void DrawComponents(Entity entity);
	};
}