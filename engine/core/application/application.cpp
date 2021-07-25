
#include "application.h"

namespace Bubble
{
    Application::Application(){}

	void Application::PushLayer(Layer* layer)
	{
		mLayers.Push(layer);
	}

	void Application::InsertLayer(int id, Layer* layer)
	{
        mLayers.Insert(id, layer);
	}

    void Application::RemoveLayer(int id)
    {
        mLayers.Remove(id);
    }

	void Application::SwapLayers(int id_1, int id_2)
	{
        mLayers.Swap(id_1, id_2);
	}

    void Application::Run()
	{
        while (mEngine.GetWindow().IsOpen())
        {
			mEngine.GetInput().NewFrame();
            mTimer.Update();

            // Retrieve and send events
            SDL_Event event;
            while (mEngine.GetWindow().PollEvent(event))
            {
                for (auto& layer : mLayers)
                {
                    layer->OnEvent(event);
                }
                mEngine.OnEvent(event);
            }

            // Update layers
            for (auto& layer : mLayers)
            {
                layer->OnUpdate(mTimer.GetDeltaTime());
            }

            // Swap image
            mEngine.OnUpdate();
        }
	}

}