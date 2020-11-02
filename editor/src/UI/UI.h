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
		ImGuiControll* mImGuiControll;
		SceneCamera* mCamera;
		Viewport* mViewport;
		Scene* mScene;
	};

	// ========== User Interface ===========
	struct UI
	{
		UIArgs mArgs;

		// Models
		bool mIsOpenModelExplorer = true;
		ModelExplorer mModelExplorer;

		// Scene
		bool mIsOpenSceneExplorer = true;
		bool mIsOpenEntityProperties = true;
		SceneExplorer mSceneExplorer;

		// Rendering options
		//DrawType mDrawTypeOption = DrawType::TRIANGLES;

		void Draw(DeltaTime dt);
		void DrawMenuBar();
		
	};

}