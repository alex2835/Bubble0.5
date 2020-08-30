
#include "SDL2/SDL.h"

#include "engine.h"
#include "entry_point.h"

#include "sdl_window/sdl_window.h"
#include "editor_layer/editor_layer.h"

namespace Bubble
{
    class EditorApp : public Application
    {
    public:
        EditorApp() : Application(new SDL_WINDOW())
        {
            PushLayer(new EditorLayer());
        }

        ~EditorApp()
        {
            SDL_Quit();
        }
    };
}


/*
	Will be called in main loop
*/
Bubble::Application* CreateApplication()
{
    return new Bubble::EditorApp();
}
