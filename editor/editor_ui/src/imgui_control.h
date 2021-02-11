#pragma once

#include "core/window.h"
#include "core/application.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


namespace Bubble
{
    class ImGuiControl
    {
		Window* mWindow;

		void ImGuiMultiViewports();

    public:
        ImGuiControl(Window* window);

        void OnAttach();
        void OnDetach();

        // ImGui scope
        void Begin();
        void End();

		void BeginMenuBar();
		void EndMenuBar();

        void OnEvent(SDL_Event& event);
    };
}