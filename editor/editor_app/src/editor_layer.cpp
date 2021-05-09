
#include "editor_layer.h"

namespace Bubble
{
	EditorLayer::EditorLayer(Window& window, Input& input)
		: mSceneCamera(input, glm::vec3(0.0f, 5.0f, 0.0f)),
		  mViewport(800, 800),
	      mWindow(window),
		  mInput(input),
		  mUILoader(window),
		  mRenderer(mLoader)
	{}

	void EditorLayer::OnAttach()
	{
		// Temp: load scene
		//ProjectDeserialization("../../../../../scene_test.json", mLoader, mRenderer, mScene);
 	}

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// ====================== Update editor ======================
		mUILoader.mArgs.mRenderer	  = &mRenderer;
		mUILoader.mArgs.mLoader		  = &mLoader;
		mUILoader.mArgs.mInput		  = &mInput;
		mUILoader.mArgs.mScene		  = &mScene;
		mUILoader.mArgs.mSceneCamera  = &mSceneCamera;
		mUILoader.mArgs.mMainViewport = &mViewport;
		mUILoader.OnUpdate(dt);

		// ====================== Set scene data ======================
		mRenderer.SetViewport(mViewport);
		mRenderer.SetCamera(mSceneCamera);

		// ====================== Draw scene ======================
		mRenderer.DrawScene(mScene);

		// Temp: Hot keys
		if (mInput.IsKeyClick(SDLK_LALT) && mInput.IsKeyClick(SDLK_F4))
		{
			mWindow.Close();
		}
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mUILoader.OnEvent(event);
	}

}