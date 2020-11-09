#pragma once

#include "engine.h"

#include "imgui_controll/imgui_controll.h"
#include "sdl_window/sdl_window.h"
#include "scene_camera/scene_camera.h"

#include "user_interface/user_interface.h"

#include "draw_tools/draw_selected_entity.h"
#include "draw_tools/draw_boundingbox.h"


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

		// Temp:
		Ref<Skybox> mSkyboxFirst;
		Ref<Skybox> mSkyboxSecond;

	public:
		EditorLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}