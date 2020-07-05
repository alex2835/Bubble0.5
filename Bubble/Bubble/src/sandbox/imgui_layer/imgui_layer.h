#pragma once

#include "layers/layer.h"
#include "../sdl_window/sdl_window.h"
#include "framebuffer/framebuffer.h"
#include "application/application.h"


namespace Sandbox
{
    struct ImGuiLayer : Bubble::Layer
    {
        SDL_WINDOW* m_Window;
        Bubble::Framebuffer m_Framebuffer;

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