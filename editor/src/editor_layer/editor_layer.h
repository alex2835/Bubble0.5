#pragma once

#include "engine.h"

#include "viewport/viewport_array.h"
#include "imgui_controll/imgui_controll.h"
#include "sdl_window/sdl_window.h"
#include "scene_camera/scene_camera_controller.h"

#include "UI/UI.h"
#include "serialization/serialization.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		UI UserInterface;
		ImGuiControll ImGuiControll;
		SceneCameraController SceneCamera;
		Viewport MainViewport;
		Scene ActiveScene;

		Ref<Shader> ShaderSelected;
		Ref<Shader> PhongShader;

		Ref<Shader> m_ShaderSkybox;
		Ref<Skybox> m_Skybox;
		
		// Temp:
		LightArray  m_Lights;
		Ref<Model>  m_NanoSuit;
		Ref<Model>  m_GrassPlane;
		Ref<Model>  m_Tree;

		void DrawMenuBar();
		
	public:
		EditorLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}