
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
		mUILoader.mArgs = GetUIArgs();
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

	UIArgs EditorLayer::GetUIArgs()
	{
		UIArgs args;
		args.mEngine	   = &mEngine;
		args.mProject	   = &mEngine.GetProject();
		args.mRenderer	   = &mEngine.GetRenderer();
		args.mLoader	   = &mEngine.GetLoader();
		args.mInput		   = &mEngine.GetInput();
		args.mScene		   = &mEngine.GetScene();
		args.mSceneCamera  = &mSceneCamera;
		args.mMainViewport = &mViewport;
		return args;
	}

}