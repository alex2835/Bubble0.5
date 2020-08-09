
#include "SDL2/SDL.h"

#include "engine.h"
#include "entry_point.h"

#include "sdl_window/sdl_window.h"
#include "editor_layer/editor_layer.h"

namespace Bubble
{
    struct EditorApp : Application
    {
        EditorApp() : Application(new SDL_WINDOW())
        {
            PushLayer(new EditorLayer((SDL_WINDOW*)m_Window.get()));
        }

        ~EditorApp()
        {
            SDL_Quit();
        }
    };
}

/*
    Will be called in embedded main loop
*/
Bubble::Application* CreateApplication()
{
    return new Bubble::EditorApp();
}
