#pragma once

#include "core/window.h"
#include "core/application.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


namespace Bubble
{
    class ImGuiControll
    {
		Window* mWindow;

		void ImGuiDocking();
		void ImGuiMultiViewports();

    public:
        ImGuiControll();

        void OnAttach();
        void OnDetach();

        // Imgui scope
        void Begin();
        void End();

		void BeginMenuBar();
		void EndMenuBar();

        void OnEvent(SDL_Event& event);
    };
}