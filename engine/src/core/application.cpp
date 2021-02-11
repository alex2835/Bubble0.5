
#include "application.h"

namespace Bubble
{
	Application::Application()
    {
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

	void Application::Run()
	{
        while (mWindow.IsOpen())
        {
			//Input::NewFrame();
            mTimer.Update();

            // Retrieve and send events
            SDL_Event event;
            while (mWindow.PollEvent(event))
            {
                for (auto& layer : mLayerArray)
                {
                    layer->OnEvent(event);
                }
                mWindow.OnEvent(event);
                //Input::OnEvent(event);
            }

            // Update layers
            for (auto& layer : mLayerArray)
            {
                layer->OnUpdate(mTimer.GetDeltaTime());
            }

            // Swap image
            mWindow.OnUpdate();
        }
	}

}