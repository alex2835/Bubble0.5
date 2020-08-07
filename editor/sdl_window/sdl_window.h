#pragma once

#include <SDL2/SDL.h>

#include "core/window/window.h"
#include "core/log/log.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 
#include "GL/glew.h"

#include "cassert"


namespace Editor
{

    struct SDL_WINDOW : Bubble::Window
    {
    public:
        SDL_WINDOW();

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

    private:
        SDL_Window* m_Window;
        SDL_GLContext m_GLContext;
        const char* glsl_version = "#version 330";
        bool m_IsOpen = true;
        bool m_ShouldClose = false;
    };

}