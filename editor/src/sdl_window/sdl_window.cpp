
#include "sdl_window.h"


namespace Bubble
{
    SDLWindow::SDLWindow()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            LOG_CORE_ERROR("Error: {}", SDL_GetError());
			throw std::runtime_error("Error: SDL init");
		}
        
        // GL 4.2 + GLSL 420
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        mWindow = SDL_CreateWindow("Bubble", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
        mGLContext = SDL_GL_CreateContext(mWindow);

        SDL_GL_MakeCurrent(mWindow, mGLContext);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        if (int error = glewInit(); error != GLEW_OK)
        {
            LOG_CORE_ERROR("Error: Glew init \n{}", glewGetErrorString(error));
            throw std::runtime_error("Window can't be created");
        }
    }

	SDLWindow::~SDLWindow()
	{
		SDL_GL_DeleteContext(mGLContext);
		SDL_DestroyWindow(mWindow);
	}

	bool SDLWindow::IsOpen()
	{
        return mIsOpen;
	}

	int SDLWindow::GetWidth()
    {
        int width = 0, height = 0;
        SDL_GetWindowSize(mWindow, &width, &height);
        return width;
    }

    int SDLWindow::GetHeight()
    {
		int width = 0, height = 0;
        SDL_GetWindowSize(mWindow, &width, &height);
        return height;
    }

	glm::ivec2 SDLWindow::GetSize()
	{
		int width = 0, height = 0;
		SDL_GetWindowSize(mWindow, &width, &height);
        return glm::ivec2(width, height);
	}

	SDL_Window* SDLWindow::GetWindow()
    {
        return mWindow;
    }

    SDL_GLContext SDLWindow::GetGLContext()
    {
        return mGLContext;
    }

    const char* SDLWindow::GetGLSLVersion()
    {
        return glsl_version;
    }

    bool SDLWindow::PollEvent(SDL_Event& event)
    {
        return SDL_PollEvent(&event);
    }

    void SDLWindow::OnEvent(SDL_Event& event)
    {
        if (event.type == SDL_QUIT)
        {
            mIsOpen = false;
        }
        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(mWindow))
        {
            mIsOpen = false;
        }
    }

    void SDLWindow::OnUpdate()
    {
        SDL_GL_SwapWindow(mWindow);
    }

    void SDLWindow::Close()
    {
        mIsOpen = false;
    }

	void SDLWindow::SetVSync(bool mode)
	{
        SDL_GL_SetSwapInterval(mode);
	}

}