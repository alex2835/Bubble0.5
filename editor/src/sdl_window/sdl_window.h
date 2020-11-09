#pragma once

#include "SDL2/SDL.h"

#include "renderer/renderer_base.h"
#include "core/window/window.h"

namespace Bubble
{
    class SDLWindow: public Window
    {
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
        const char* glsl_version = "#version 420";
        bool mIsOpen = true;

    public:
        SDLWindow();
        ~SDLWindow();

        bool IsOpen() override;
        
        int GetWidth() override;
        int GetHeight() override;
        glm::ivec2 GetSize() override;

        SDL_Window* GetWindow();
        SDL_GLContext GetGLContext();
        const char* GetGLSLVersion();

        bool PollEvent(SDL_Event& event) override;
        void OnEvent(SDL_Event& event) override;

        void OnUpdate() override;
        void Close() override;

        void SetVSync(bool mode) override;
    };
}