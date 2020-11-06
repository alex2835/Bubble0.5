#pragma once

#include "SDL2/SDL.h"

#include "renderer/renderer_base.h"
#include "core/window/window.h"

#include "cassert"


namespace Bubble
{
    class SDL_WINDOW: public Window
    {
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
        const char* glsl_version = "#version 420";
        bool mIsOpen = true;

    public:
        SDL_WINDOW();
        ~SDL_WINDOW();

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