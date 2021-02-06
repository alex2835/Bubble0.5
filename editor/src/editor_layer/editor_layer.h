#pragma once

#include "engine.h"
#include "core/window.h"

#include "imgui_controll/imgui_controll.h"
#include "scene_camera/scene_camera.h"

#include "user_interface/user_interface.h"

#include "draw_tools/draw_selected_entity.h"
#include "draw_tools/draw_boundingbox.h"

#include "serialization/serialization.h"



namespace Bubble
{
	class EditorLayer : public Layer
	{
		UI mUI;
		ImGuiControll mImGuiControll;
		SceneCamera mSceneCamera;
		Viewport mViewport;
		Scene mScene;

		// Options
		bool mClearScreanOption = false;

	public:
		EditorLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}