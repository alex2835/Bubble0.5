#pragma once

#include "engine.h"
#include "imgui_controll/imgui_controll.h"

namespace Editor
{
	struct EditorLayer : Bubble::Layer
	{
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(SDL_Event& event) override;

	private:
		ImGuiControll m_ImGuiControll;

		// test vars
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	};
}