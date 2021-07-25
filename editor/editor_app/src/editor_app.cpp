
#include "bubble_entry_point.h"
#include "editor_layer.h"
namespace Bubble
{
    class EditorApp : public Application
    {
    public:
        EditorApp() : Application()
        {
            PushLayer(new EditorLayer(mEngine));
        }

        ~EditorApp()
        {
            SDL_Quit();
        }
    };
}

// Will be called in main loop
Bubble::Application* CreateApplication()
{
    return new Bubble::EditorApp();
}
