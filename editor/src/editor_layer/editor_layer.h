#pragma once

#include "engine.h"

#include "viewport/viewport_array.h"
#include "imgui_controll/imgui_controll.h"
#include "sdl_window/sdl_window.h"
#include "scene_camera/scene_camera_controller.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		ImGuiControll m_ImGuiControll;
		ViewportArray m_ViewportArray;
		Ref<Scene> m_Scene;

		SceneCameraController m_SceneCamera;

		// Temp:
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<Texture2D> m_Texture;
		Scope<Shader> m_Shader;

		Ref<Shader> m_ShaderPhong;
		Ref<Model> m_NanoSuit;

		Entity m_Entity;

	public:
		EditorLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}