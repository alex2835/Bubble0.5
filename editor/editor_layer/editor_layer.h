#pragma once

#include "engine.h"

#include "viewport/viewport_array.h"
#include "imgui_controll/imgui_controll.h"
#include "sdl_window/sdl_window.h"

namespace Bubble
{
	struct EditorLayer : Layer
	{
	private:
		ImGuiControll m_ImGuiControll;
		ViewportArray m_ViewportArray;

		// Temp:
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	public:
		EditorLayer(SDL_WINDOW* window);
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(SDL_Event& event) override;
	};
}