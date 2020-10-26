#pragma once

#include "imgui.h"
#include "imgui_controll/imgui_controll.h"
#include "serialization/serialization.h"

#include "UI_components/model_explorer.h"
#include "UI_components/scene_camera_options.h"
#include "UI_components/scene_explorer.h"
#include "UI_components/main_viewport.h"


namespace Bubble
{
	struct UIArgs
	{
		ImGuiControll* ImGuiControll;
		SceneCamera* Camera;
		Viewport* MainViewport;
		Scene* ActiveScene;
	};

	// ========== User Interface ===========
	struct UI
	{
		UIArgs Args;

		// Models
		bool IsOpenModelExplorer = true;
		ModelExplorer ModelExplorerPanel;

		// Scene
		bool IsOpenSceneExplorer = true;
		bool IsOpenEntityProperties = true;
		SceneExplorer SceneExplorerPanel;

		// Rendering options
		DrawType DrawTypeOption = DrawType::TRIANGLES;

		void Draw(DeltaTime dt);
		void DrawMenuBar();
		
	};

}