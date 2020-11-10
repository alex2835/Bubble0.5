#pragma once

#include "imgui.h"
#include "imgui_controll/imgui_controll.h"

#include "ui_components/model_explorer.h"
#include "ui_components/scene_camera_options.h"
#include "ui_components/scene_explorer_panel.h"
#include "ui_components/main_viewport.h"
#include "ui_components/skybox_exolorer.h"
#include "ui_components/scene_panel.h"

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
		bool mIsOpenModelExplorer = false;
		ModelExplorer mModelExplorer;

		// Scene
		bool mIsOpenSceneExplorer = true;
		bool mIsOpenEntityProperties = true;
		SceneExplorerPanel mSceneExplorerPanel;

		// Scene panel
		bool mIsOpenScenePanel = true;
		ScenePanel mScenePanel;

		// Skybox
		bool mIsOpenSkyboxExplorer = false;
		SkyboxExplorer mSkyboxExplorer;

		// Rendering options
		bool mWireframeOption = false;
		bool mBoundingBoxOption = false;

		void Draw(DeltaTime dt);
		void DrawMenuBar();
	};

}