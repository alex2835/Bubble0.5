#pragma once

#include "window/window.h"
#include <SDL2/SDL.h>
#include "log/log.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 

#define GLEW_STATIC
#include "GL/glew.h"

#include "cassert"

namespace Editor
{

    struct SDL_WINDOW : Bubble::Window
    {
        SDL_Window* m_Window;
        SDL_GLContext m_GL_Context;
        
        const char* glsl_version = "#version 330";
        bool m_Open = true;
        bool m_Closing = false;

        SDL_WINDOW();

        bool isOpen() override;
        
        int GetWindth() override;
        int GetHeight() override;

        SDL_Window* GetWindow();
        SDL_GLContext GetContext();
        const char* GetGLSLVersion();

        bool PollEvent(SDL_Event& event) override;
        void OnEvent(SDL_Event& event) override;

        void OnUpdate() override;
        void Close() override;
    };

}