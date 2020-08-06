
#include "SDL2/SDL.h"

#include "engine.h"

#include "sdl_window/sdl_window.h"
#include "imgui_layer/imgui_layer.h"
#include "viewport/viewports.h"

namespace Editor
{
    // Temp: Create new viewport by pressing space
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
                viewports.Push(Viewport(200, 100));
        }
    };


    struct Editor : Bubble::Application
    {
        Editor() : Application(new SDL_WINDOW())
        {
            viewports.Push(Viewport(200, 100));

            PushLayer(new TestLayer());
            PushLayer(new ImGuiLayer());
        }

        ~Editor()
        {
            SDL_Quit();
        }
    };

}

/*
    Will be called in embeded main loop
*/
Bubble::Application* Bubble::CreateApplication()
{
    return new Editor::Editor();
}

