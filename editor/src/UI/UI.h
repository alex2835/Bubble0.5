#pragma once

#include "imgui.h"
#include <vector>

#include "UI_components/model_loading.h"
#include "UI_components/scene_camera_options.h"
#include "UI_components/scene_explorer.h"



namespace Bubble
{
	struct UIArgs
	{
		std::vector<Ref<Model>>* Models;
		SceneCameraController* Camera;
		// Rendering
		DrawType* DrawTypeOption;

		// Scene
		Scene* ActiveScene;
	};

	// ========== User Interface ===========

	class UI
	{
	public:
		// Information from editor layer
		// that will be displayed
		UIArgs Args;

		// Models
		bool IsOpenModelLoader = false;

		// Scene
		bool IsOpenSceneExplorer = true;
		bool IsOpenEntityProperties = true;
		SceneExplorerPanel ExplorerPanel;
		
		void Draw();
		void DrawMenuOptions();
		
	};

}