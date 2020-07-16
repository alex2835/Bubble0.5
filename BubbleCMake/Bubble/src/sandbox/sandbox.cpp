
//#include "pch.h"
#include "SDL2/SDL.h"
#include "engine.h"

#include "sdl_window/sdl_window.h"
#include "imgui_layer/imgui_layer.h"


namespace Sandbox
{
    struct Sandbox : Bubble::Application
    {
        Sandbox() : Application(new SDL_WINDOW())
        {
            push_layer(new ImGuiLayer());
        }

        ~Sandbox()
        {
            SDL_Quit();
        }
    };

}

// Mainloop embedded in application class
Bubble::Application* Bubble::create_application()
{
    return new Sandbox::Sandbox();
}

