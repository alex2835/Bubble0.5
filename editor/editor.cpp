
#include "SDL2/SDL.h"
#include "engine.h"

#include "sdl_window/sdl_window.h"
#include "imgui_layer/imgui_layer.h"
#include "viewport/viewports.h"

namespace Editor
{
    struct TestLayer : Bubble::Layer
    {
        TestLayer(): Layer("test layer") {};
        
        void OnAttach() override {}
        void OnDetach() override {}
        void OnUpdate() override {}
        void OnEvent(SDL_Event& event) override 
        {
            if (event.type == SDL_EventType::SDL_KEYDOWN
                && event.key.keysym.sym == SDLK_SPACE)
                viewports.push_back(200, 100);
        }
    };

    struct Editor : Bubble::Application
    {
        Editor() : Application(new SDL_WINDOW())
        {
            viewports.push_back(Viewport(200, 100));
            push_layer(new TestLayer());
            push_layer(new ImGuiLayer());
        }

        ~Editor()
        {
            SDL_Quit();
        }
    };

}

// Mainloop embedded in application class
Bubble::Application* Bubble::create_application()
{
    return new Editor::Editor();
}

