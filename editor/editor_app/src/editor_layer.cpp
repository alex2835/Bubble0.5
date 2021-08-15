
#include "editor_layer.h"

namespace Bubble
{
	EditorLayer::EditorLayer(Engine& engine)
		: mSceneCamera(engine.GetInput(), glm::vec3(0.0f, 5.0f, 0.0f)),
		  mViewport(800, 800),
		  mUILoader(engine.GetWindow()),
		  mEngine(engine)
	{}

	void EditorLayer::OnAttach()
	{
		// Temp: load scene
		//ProjectDeserialization("C:/Users/lol/Desktop/projects/BubbleOld_prj/BubbleOld/test_project/test.bubble", mEngine);
        mEngine.GetProject().Open("C:/Users/lol/Desktop/projects/BubbleOld_prj/BubbleOld/test_project/test.bubble");
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// ====================== Update editor ======================
		mUILoader.mArgs.mEngine		  = &mEngine;
		mUILoader.mArgs.mProject      = &mEngine.GetProject();
		mUILoader.mArgs.mRenderer	  = &mEngine.GetRenderer();
		mUILoader.mArgs.mLoader		  = &mEngine.GetLoader();
		mUILoader.mArgs.mInput		  = &mEngine.GetInput();
		mUILoader.mArgs.mScene		  = &mEngine.GetScene();
		mUILoader.mArgs.mSceneCamera  = &mSceneCamera;
		mUILoader.mArgs.mMainViewport = &mViewport;
		mUILoader.OnUpdate(dt);

		// ====================== Set scene data ======================
		mEngine.GetRenderer().SetViewport(mViewport);
		mEngine.GetRenderer().SetCamera(mSceneCamera);

		// ====================== Draw scene ======================
		mEngine.GetRenderer().DrawScene(mEngine.GetScene());

		// Temp: Hot keys
		if (mEngine.GetInput().IsKeyClick(SDLK_LALT) && mEngine.GetInput().IsKeyClick(SDLK_F4))
			mEngine.GetWindow().Close();
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mUILoader.OnEvent(event);
	}

}