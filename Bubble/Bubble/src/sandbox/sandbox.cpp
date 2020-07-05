
#include "pch.h"
#include "engine.h"

#include "sdl_window/sdl_window.h"
#include "imgui_layer/imgui_layer.h"


namespace Sandbox
{
    struct Sandbox : Bubble::Application
    {
        Sandbox()
        {
            sdl_window* window = new sdl_window();

            setWindow(window);
            push_layer(new ImGuiLayer(window));
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

