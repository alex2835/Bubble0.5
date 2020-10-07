#pragma once

#include "sdl_window/sdl_window.h"

#include "imgui.h"
#include "application/application.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


namespace Bubble
{
    class ImGuiControll
    {
		SDL_WINDOW* m_Window;
        void(*MenuBar)();

		void ImGuiDocking();
		void ImGuiMultiViewports();

    public:
        ImGuiControll();

        void OnAttach();
        void OnDetach();

        // Imgui scope
        void Begin();
        void End();

        void OnEvent(SDL_Event& event);

        void SetMenuBar(void(*menu_bar)()) { MenuBar = menu_bar; }
    };
}