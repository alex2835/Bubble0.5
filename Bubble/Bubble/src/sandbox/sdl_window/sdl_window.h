#pragma once

#include "window/window.h"
#include "log/log.h"


namespace Sandbox
{

    struct sdl_window : Bubble::Window
    {
        SDL_Window* window;
        SDL_GLContext gl_context;
        const char* glsl_version = "#version 130";
        bool open = true;
        bool closing = false;

        sdl_window();

        bool isOpen() override;
        
        int getWindth() override;
        int getHeight() override;

        bool PollEvent(SDL_Event& event);
        void OnEvent(SDL_Event& event) override;

        void OnUpdate() override;
        void Close() override;
    };

}