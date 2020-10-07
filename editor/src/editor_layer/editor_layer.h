#pragma once

#include "engine.h"

#include "viewport/viewport_array.h"
#include "imgui_controll/imgui_controll.h"
#include "sdl_window/sdl_window.h"
#include "scene_camera/scene_camera_controller.h"

#include "UI/UI.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		UI UserInterface;
		ImGuiControll ImGuiControll;
		ViewportArray ViewportArray;
		
		std::vector<Ref<Model>> Models;
		SceneCameraController SceneCamera;
		
		std::vector<Entity> Entities;
		Ref<Scene> ActiveScene;

		Ref<Shader> m_ShaderSkybox;
		Ref<Skybox> m_Skybox;

		// rendering options
		DrawType DrawTypeOption = DrawType::TRIANGLES;

		// Temp:
		LightArray  m_Lights;
		Ref<Shader> m_ShaderPhong;
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