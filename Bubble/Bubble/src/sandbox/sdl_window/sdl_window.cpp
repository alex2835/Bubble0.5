
#include "pch.h"
#include "sdl_window.h"


namespace Sandbox
{
    sdl_window::sdl_window()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            LOG_ERROR("Error: {0}\n", SDL_GetError());
            open = false;
            return;
        }

        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

        window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
        gl_context = SDL_GL_CreateContext(window);

        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        if (glewInit() != GLEW_OK)
        {
            LOG_ERROR("Error: {0}\n", "Glew init problem");
            open = false;
            return;
        }
    }

    bool sdl_window::isOpen()
    {
        return open;
    }

    int sdl_window::getWindth()
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(window, &w, &h);
        return w;
    }

    int sdl_window::getHeight()
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(window, &w, &h);
        return h;
    }

    bool sdl_window::PollEvent(SDL_Event& event)
    {
        return SDL_PollEvent(&event);
    }

    void sdl_window::OnEvent(SDL_Event& event)
    {
        if (event.type == SDL_QUIT)
            closing = true;

        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(window))
        {
            closing = true;
        }
    }

    void sdl_window::OnUpdate()
    {
        SDL_GL_SwapWindow(window);

        if (closing) 
            Close();
    }

    void sdl_window::Close()
    {
        open = false;
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
    }

}