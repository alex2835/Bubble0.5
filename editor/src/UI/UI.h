#pragma once

#include "imgui.h"
#include <vector>

#include "UI_components/model_explorer.h"
#include "UI_components/scene_camera_options.h"
#include "UI_components/scene_explorer.h"



namespace Bubble
{
	struct UIArgs
	{
		std::vector<Ref<Model>>* Models;
		SceneCameraController* Camera;

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
		bool IsOpenModelExplorer = true;
		ModelExplorer ModelExplorerPanel;

		// Scene
		bool IsOpenSceneExplorer = true;
		bool IsOpenEntityProperties = true;
		SceneExplorer SceneExplorerPanel;

		// rendering options
		DrawType DrawTypeOption = DrawType::TRIANGLES;
		
		void Draw();
		void DrawMenuOptions();
		
	};

}