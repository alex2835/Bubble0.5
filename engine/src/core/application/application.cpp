
#include "application.h"


namespace Bubble
{
    Window* Application::s_CurrentWindow = nullptr;
	std::string* Application::s_CurrentDir = nullptr;


	Application::Application(Window* window)
        : mWindow(window)
    {
        Application::s_CurrentWindow = window;
    }

	void Application::PushLayer(Layer* layer)
	{
		mLayerArray.Push(layer);
	}

	void Application::InsertLayer(int id, Layer* layer)
	{
        mLayerArray.Insert(id, layer);
	}

    void Application::RemoveLayer(int id)
    {
        mLayerArray.Remove(id);
    }

	void Application::SwapLayers(int id_1, int id_2)
	{
        mLayerArray.Swap(id_1, id_2);
	}

	Window* Application::GetWindow()
	{
        return s_CurrentWindow;
	}

	void Application::SetCurrentDir(const std::string& path)
	{
        int path_size = std::min(path.find("/Bubble"), path.size());
        mCurrentDir = path.substr(0, path_size);
        s_CurrentDir = &mCurrentDir;
	}

	const std::string& Application::GetCurrentDir()
	{
        return *s_CurrentDir;
	}

	void Application::Run()
	{
        Renderer::Init();

        while (mWindow.get() && mWindow->IsOpen())
        {
			Input::NewFrame();
            mTimer.Update();

            // Retrieve and send events
            SDL_Event event;
            while (mWindow->PollEvent(event))
            {
                for (auto& layer : mLayerArray)
                {
                    layer->OnEvent(event);
                }
                mWindow->OnEvent(event);
                Input::OnEvent(event);
            }

            // Update layers
            for (auto& layer : mLayerArray)
            {
                layer->OnUpdate(mTimer.GetDeltaTime());
            }

            // Update window
            mWindow->OnUpdate();
        }
	}

}