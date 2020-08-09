#pragma once

#include "sdl_window/sdl_window.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


namespace Bubble
{
    struct ImGuiControll
    {
        SDL_WINDOW* m_Window;

        ImGuiControll(SDL_WINDOW* window);

        void OnAttach();
        void OnDetach();

        // Imgui scope
        void Begin();
        void End();

        void OnEvent(SDL_Event& event);
    };
}