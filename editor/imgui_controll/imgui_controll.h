#pragma once

#include "engine.h"

#include "sdl_window/sdl_window.h"
#include "viewport/viewports.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


namespace Editor
{
    struct ImGuiControll
    {
        SDL_WINDOW* m_Window;

        ImGuiControll();

        void OnAttach();
        void OnDetach();

        void Begin();
        void End();

        void OnEvent(SDL_Event& event);
    };
}