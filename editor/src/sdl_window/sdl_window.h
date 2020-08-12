#pragma once

#include "SDL2/SDL.h"

#include "renderer/renderer_base.h"
#include "core/window/window.h"

#include "cassert"


namespace Bubble
{
    class SDL_WINDOW: public Window
    {
        SDL_Window* m_Window;
        SDL_GLContext m_GLContext;
        const char* glsl_version = "#version 330";
        bool m_IsOpen = true;
        bool m_ShouldClose = false;

    public:
        SDL_WINDOW();
        ~SDL_WINDOW();

        bool IsOpen() override;
        
        int GetWindth() override;
        int GetHeight() override;

        SDL_Window* GetWindow();
        SDL_GLContext GetGLContext();
        const char* GetGLSLVersion();

        bool PollEvent(SDL_Event& event) override;
        void OnEvent(SDL_Event& event) override;

        void OnUpdate() override;
        void Close() override;
    };
}