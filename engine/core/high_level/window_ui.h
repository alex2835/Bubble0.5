#pragma once

#include "application/window.h"
#include "viewport.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

namespace Bubble
{
    struct ImGuiControl
    {
		Window& mWindow;
        ImGuiContext* mContext;

        ImGuiControl(Window& window);
        void OnAttach();
        void OnDetach();

        void Begin();
        void End();

        void OnEvent(SDL_Event& event);
        void ImGuiMultiViewports();
        void BeginMenuBar();
        void EndMenuBar();
    };
}