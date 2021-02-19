
#include "editor_layer.h"

namespace Bubble
{
	EditorLayer::EditorLayer(Window* window, Input* input)
		: mSceneCamera(input, glm::vec3(0.0f, 5.0f, 0.0f)),
		  mViewport(800, 800),
	      mWindow(window),
		  mInput(input),
		  mUILoader(window),
		  mRenderer(&mLoader)
	{}

	void EditorLayer::OnAttach()
	{
		// Temp: load scene
		//OpenProject("../../../../scene_test.json", &mScene, &mUILoader);

 	}

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// ====================== Update editor ======================
		mUILoader.mArgs.mRenderer	  = &mRenderer;
		mUILoader.mArgs.mLoader		  = &mLoader;
		mUILoader.mArgs.mInput		  = mInput;
		mUILoader.mArgs.mScene		  = &mScene;
		mUILoader.mArgs.mSceneCamera  = &mSceneCamera;
		mUILoader.mArgs.mMainViewport = &mViewport;
		mUILoader.OnUpdate(dt);

		// ====================== Set scene data ======================
		mRenderer.SetViewport(mViewport);
		mRenderer.SetCamera(mSceneCamera);

		// ====================== Draw scene ======================
		if (mRenderer.mSceneStage.mSkyboxFirst &&
			mRenderer.mSceneStage.mSkyboxSecond)
		{
            mRenderer.mBackgroundType = BackgroundType::SKYBOX;
		}
		else {
            mRenderer.mBackgroundType = BackgroundType::COLOR;
		}
		mRenderer.mBackgroundType = BackgroundType::SKYSPHERE;

		mRenderer.DrawScene(mScene);

		// ====================== Draw editor sruff ======================
		//mRenderer.SetCamera(mSceneCamera);
		//Entity selected_entity = mUILoader.mEntityExplorer->SelectedEntity;

		//// Highlight selected entity
		//if (selected_entity)
		//{
		//	draw_selected_model(selected_entity);
		//}
		
		// Draw bounding boxes
        //if (mUILoader.mBoundingBoxOption)
        //{
        //    draw_scene_boundingbox(mScene);
        //}

		// Temp: Hot keys
		if (mInput->IsKeyClick(SDLK_LALT) && mInput->IsKeyClick(SDLK_F4))
		{
			mWindow->Close();
		}
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mUILoader.OnEvent(event);
	}

}