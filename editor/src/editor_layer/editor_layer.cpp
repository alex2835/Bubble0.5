
#include "editor_layer.h"


namespace Bubble
{
	EditorLayer::EditorLayer()
		: mSceneCamera(glm::vec3(0.0f, 5.0f, 0.0f))
	{}

	void EditorLayer::OnAttach()
	{
        mImGuiControll.OnAttach();

		mViewport = Viewport(800, 800);

		// ============ Model entities =============
	
		OpenProject("../../../../scene_test.json", &mScene);

		// Temp: skybox
		mActiveSkybox = SkyboxLoader::Load("resources/skybox/skybox1.jpg");
		mSkyboxShader = ShaderLoader::Load("resources/shaders/skybox.glsl");
		
		mPhongShader = ShaderLoader::Load("resources/shaders/phong.glsl");

		
		// Temp: Try to simplify mesh
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
		mSceneCamera.OnUpdate(dt);


		// ====================== Set uniform data ======================
		Renderer::SetViewport(mViewport);
		Renderer::SetCamera(mSceneCamera);

		// Temp : Apply lights to shader
		int light_index = 0;
		mScene.Registry.view<LightComponent>().each(
			[&](auto entity, LightComponent& lc)
			{
				lc.mLight.SetDistance();
				Light::ApplyLight(lc.mLight, mPhongShader, light_index++);
			}
		);
		mPhongShader->SetUni1i("nLights", light_index);


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


		// ========================= Draw skybox ========================= 
		glm::mat4 view = Renderer::ActiveCamera->GetLookatMat();

		float rotation = glm::radians(Timer::GetTime().GetSeconds() * 0.5f);
		view = glm::rotate(view, rotation, glm::vec3(0, 1, 0));
		view = glm::mat4(glm::mat3(view));

		Renderer::GetUBOPojectionView()[0].SetMat4("View", view);


		mSkyboxShader->SetUni1f("u_Brightness", 1.0f);
		Renderer::DrawSkybox(mActiveSkybox, mSkyboxShader);


		// Quit closure
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