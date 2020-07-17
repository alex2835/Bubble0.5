
//#include "pch.h"
#include "application.h"

namespace Bubble
{
    Window* Application::s_Window = NULL;

    Application::Application(Window* window)
    {
        s_Window = window;
    }

    Application::~Application() 
    {
        delete s_Window;
    }

    // ================== Layers ======================
	void Application::push_layer(Layer* layer)
	{
		m_LayerArray.push_back(layer);
	}

	void Application::emplace_layer(int id, Layer* layer)
	{
        m_LayerArray.emplace(id, layer);
	}

    void Application::remove_layer(int id)
    {
        m_LayerArray.remove(id);
    }

	void Application::swap_layers(int id_1, int id_2)
	{
        m_LayerArray.swap(id_1, id_2);
	}

   
    // =================== Window ====================
    void Application::SetWindow(Window* window)
    {
        s_Window = window;
    }

    Window* Application::GetWindow()
    {
        return s_Window;
    }


    // =================== Run ===================
	void Application::Run()
	{
        while (s_Window && s_Window->isOpen())
        {
            // Send events
            SDL_Event event;
            while (s_Window->PollEvent(event))
            {
                for (auto& layer : m_LayerArray)
                    layer->OnEvent(event);
                
                s_Window->OnEvent(event);
            }
            
            // Update layers
            for (auto& layer : m_LayerArray)
                layer->OnUpdate();

            // render window
            s_Window->OnUpdate();
        }
	}

}