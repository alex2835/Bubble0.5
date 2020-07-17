#pragma once

#include "../sdl_window/sdl_window.h"
#include "../viewport/viewports.h"

#include "layers/layer.h"
#include "framebuffer/framebuffer.h"
#include "application/application.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


namespace Editor
{
    struct ImGuiLayer : Bubble::Layer
    {
        SDL_WINDOW* m_Window;

        // test vars
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(SDL_Event& event);
    };
}