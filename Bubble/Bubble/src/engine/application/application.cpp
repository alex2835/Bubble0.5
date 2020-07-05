
#include "pch.h"
#include "application.h"

namespace Bubble
{
    Application::Application(Window* window) : window(window) {}

    Application::~Application() 
    {
        delete window;
    }

    // ================== Layers ======================
	void Application::push_layer(Layer* layer)
	{
		layer_array.push_back(layer);
	}

	void Application::emplace_layer(int id, Layer* layer)
	{
		layer_array.emplace(id, layer);
	}

    void Application::remove_layer(int id)
    {
        layer_array.remove(id);
    }

	void Application::swap_layers(int id_1, int id_2)
	{
		layer_array.swap(id_1, id_2);
	}
	

    // =================== Window ====================
    void Application::setWindow(Window* window)
    {
        this->window = window;
    }


    // =================== Run ===================
	void Application::run()
	{
        while (window && window->isOpen())
        {
            // Send events
            SDL_Event event;
            while (window->PollEvent(event))
            {
                for (auto& layer : layer_array.layers)
                    layer->OnEvent(event);
                
                window->OnEvent(event);
            }
            
            // Update layers
            for (auto& layer : layer_array.layers)
                layer->OnUpdate();

            // render window
            window->OnUpdate();
        }
	}

}