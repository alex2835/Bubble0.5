
#include "application.h"


namespace Bubble
{
    Window* Application::s_CurrentWindow = nullptr;

    Application::Application(Window* window)
        : m_Window(window)
    {
        Application::s_CurrentWindow = window;
    }

	void Application::PushLayer(Layer* layer)
	{
		m_LayerArray.Push(layer);
	}

	void Application::InsertLayer(int id, Layer* layer)
	{
        m_LayerArray.Insert(id, layer);
	}

    void Application::RemoveLayer(int id)
    {
        m_LayerArray.Remove(id);
    }

	void Application::SwapLayers(int id_1, int id_2)
	{
        m_LayerArray.Swap(id_1, id_2);
	}

	Window* Application::GetWindow()
	{
        return s_CurrentWindow;
	}

	void Application::Run()
	{
        Renderer::Init();

        while (m_Window.get() && m_Window->IsOpen())
        {
			Input::NewFrame();
            m_DeltaTime.Update(SDL_GetTicks() / 1000.0f);

            // Retrieve and send events
            SDL_Event event;
            while (m_Window->PollEvent(event))
            {
                for (auto& layer : m_LayerArray)
                {
                    layer->OnEvent(event);
                }
                m_Window->OnEvent(event);
                Input::OnEvent(event);
            }

            // Update layers
            for (auto& layer : m_LayerArray)
            {
                layer->OnUpdate(m_DeltaTime);
            }

            // Update window
            m_Window->OnUpdate();
        }
	}

}