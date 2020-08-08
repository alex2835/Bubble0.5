#pragma once

#include "layers/layer.h"
#include "application/application.h"
#include "imgui_controll/imgui_controll.h"

#include "viewport/viewport_array.h"

namespace Editor
{
	struct EditorLayer : Bubble::Layer
	{
	private:
		ImGuiControll m_ImGuiControll;
		ViewportArray m_ViewportArray;

		// test vars
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	public:
		EditorLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(SDL_Event& event) override;
	};
}