
#include "editor_layer.h"


namespace Bubble
{
	EditorLayer::EditorLayer()
		: mSceneCamera(glm::vec3(0.0f, 5.0f, 0.0f)),
		  mViewport(800, 800)
	{}

	void EditorLayer::OnAttach()
	{
        mImGuiControll.OnAttach();
	
		// Temp: load scene
		OpenProject("../../../../scene_test.json", &mScene);

		// Temp: skybox
		Renderer::SkyboxFirst = SkyboxLoader::Load("resources/skybox/skybox1.jpg");
		Renderer::SkyboxSecond = SkyboxLoader::Load("resources/skybox/skybox6.jpg");
 	}


	void EditorLayer::OnDetach()
	{
        mImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// ====================== Draw gui ======================
		mUI.mArgs = { &mImGuiControll, &mSceneCamera, &mViewport, &mScene };
		mUI.Draw(dt);


		// ====================== Update ======================
		mSceneCamera.Update(dt);

		for (Viewport* viewport : EditorViewports)
		{
			if (viewport->NewSize != viewport->GetSize())
			{
				viewport->Resize(viewport->NewSize);
			}
		}


		// ====================== Set scene data ======================
		Renderer::SetViewport(mViewport);
		Renderer::SetCamera(mSceneCamera);
		
		// Temp: Set skybox data
		Renderer::SkyboxBrightness = 1.0f;
		Renderer::SkyboxBlendFactor = 1.0f;
		Renderer::SkyboxRotation = Timer::GetTime().GetSeconds() * 0.001f;


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
		Entity selected_entity = mUI.mSceneExplorer.SelectedEntity;

		// Highlight selected entity
		if (selected_entity)
		{
			draw_selected_model(selected_entity);
		}
		
		// Draw bounding boxes
		if (mUI.mBoundingBoxOption)
		{
			draw_scene_boundingbox(mScene);
		}


		// Temp: Hot keys

		// Quit combination
		if (Input::IsKeyClick(SDLK_LALT) && Input::IsKeyClick(SDLK_F4))
		{
			Application::GetWindow()->Close();
		}
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mImGuiControll.OnEvent(event);
	}

}