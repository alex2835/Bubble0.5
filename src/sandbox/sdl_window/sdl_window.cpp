
//#include "pch.h"
#include "sdl_window.h"


namespace Sandbox
{
    SDL_WINDOW::SDL_WINDOW()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            LOG_ERROR("Error: {0}\n", SDL_GetError());
            m_Open = false;
            return;
        }
        
        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

        m_Window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
        m_GL_Context = SDL_GL_CreateContext(m_Window);

        SDL_GL_MakeCurrent(m_Window, m_GL_Context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        if (int error = glewInit(); error != GLEW_OK)
        {
            LOG_ERROR("Error: {0}", "Glew init problem", glewGetErrorString(error));
            m_Open = false;
            return;
        }
    }

    bool SDL_WINDOW::isOpen()
    {
        return m_Open;
    }

    int SDL_WINDOW::GetWindth()
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(m_Window, &w, &h);
        return w;
    }

    int SDL_WINDOW::GetHeight()
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(m_Window, &w, &h);
        return h;
    }

    SDL_Window* SDL_WINDOW::GetWindow()
    {
        return m_Window;
    }

    SDL_GLContext SDL_WINDOW::GetContext()
    {
        return m_GL_Context;
    }

    const char* SDL_WINDOW::GetGLSLVersion()
    {
        return glsl_version;
    }

    bool SDL_WINDOW::PollEvent(SDL_Event& event)
    {
        return SDL_PollEvent(&event);
    }

    void SDL_WINDOW::OnEvent(SDL_Event& event)
    {
        if (event.type == SDL_QUIT)
            m_Closing = true;

        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(m_Window))
        {
            m_Closing = true;
        }
    }

    void SDL_WINDOW::OnUpdate()
    {
        SDL_GL_SwapWindow(m_Window);

        if (m_Closing) 
            Close();
    }

    void SDL_WINDOW::Close()
    {
        m_Open = false;
        SDL_GL_DeleteContext(m_GL_Context);
        SDL_DestroyWindow(m_Window);
    }

}