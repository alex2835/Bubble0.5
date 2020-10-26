#pragma once

#include "engine.h"

#include "viewport/viewport_array.h"
#include "imgui_controll/imgui_controll.h"
#include "sdl_window/sdl_window.h"
#include "scene_camera/scene_camera.h"

#include "UI/UI.h"
#include "serialization/serialization.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		UI UserInterface;
		ImGuiControll ImGuiControll;
		SceneCamera SceneCamera;
		Viewport MainViewport;
		Scene ActiveScene;

		Ref<Shader> SelectedItemShader;
		Ref<Shader> PhongShader;

		Ref<Shader> SkyboxShader;
		Ref<Skybox> ActiveSkybox;
		
		void DrawMenuBar();
		
	public:
		EditorLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}