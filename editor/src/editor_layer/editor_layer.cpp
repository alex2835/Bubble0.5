
#include "editor_layer.h"


namespace Bubble
{
	EditorLayer::EditorLayer()
		: mSceneCamera(glm::vec3(0.0f, 5.0f, 0.0f)),
		  mViewport(800, 800),
		  mUI(&Application::GetMainWindow())
	{}

	void EditorLayer::OnAttach()
	{
		// Temp: load scene
		OpenProject("../../../../scene_test.json", &mScene, &mUI);

 	}


    void EditorLayer::OnDetach()
    {
		LOG_INFO("asdf");
    }

    void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// ====================== Update editor ======================
        mUI.mArgs = { &mSceneCamera, &mViewport, &mScene };
        mUI.OnUpdate(dt);

		mSceneCamera.Update(dt);

		// ====================== Set scene data ======================
		Renderer::SetViewport(mViewport);
		Renderer::SetCamera(mSceneCamera);


		// ====================== Rendering ======================
		mClearScreanOption |= mUI.mWireframeOption;

		if (mClearScreanOption)
		{
			Renderer::SetClearColor(glm::vec4(1.0f));
			Renderer::ClearColor();
		}
		Renderer::ClearDepth();
		
		// ====================== Draw scene ====================== 
		Renderer::DrawScene(mScene);


		// ====================== Draw editor sruff ======================
		Renderer::SetCamera(mSceneCamera);
		Entity selected_entity = mUI.mEntityExplorer->SelectedEntity;

		//// Highlight selected entity
		//if (selected_entity)
		//{
		//	draw_selected_model(selected_entity);
		//}
		
		// Draw bounding boxes
		if (mUI.mBoundingBoxOption)
		{
			draw_scene_boundingbox(mScene);
		}

		// Temp: Hot keys
		// Quit combination
		if (Input::IsKeyClick(SDLK_LALT) && Input::IsKeyClick(SDLK_F4))
		{
			Application::GetMainWindow().Close();
		}
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mUI.OnEvent(event);
	}

}