
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
		// Set args for UI
		mUI.mArgs = { &mImGuiControll, &mSceneCamera, &mViewport, &mScene };

		// User Interface
		mUI.Draw(dt);


		// Scene camera update
		mSceneCamera.OnUpdate(dt);


		Renderer::SetViewport(mViewport);
		Renderer::ClearDepth();

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

		glm::ivec2 window_size = mViewport.GetSize();
		glm::mat4 projection = mSceneCamera.GetPprojectionMat(window_size.x, window_size.y);
		glm::mat4 view = mSceneCamera.GetLookatMat();

		Renderer::SetUBOPojectionView(projection, view);
		SetFrustumPlanes(projection * view);

		// Draw scene
		Renderer::DrawScene(mScene);

		// ======================= Draw editor sruff =======================

		// Highlight selected entity
		Entity selected_entity = mUI.mSceneExplorer.SelectedEntity;
		if (selected_entity)
		{
			draw_selected_model(selected_entity);
		}
		
		// Draw boundingBox
		if (mUI.mBoundingBoxOption)
		{
			draw_scene_boundingbox(mScene);
		}


		// ========================= Draw skybox ========================= 

		float rotation_const = glm::radians(Timer::GetTime().GetSeconds() * 0.5f);
		view = glm::rotate(view, rotation_const, glm::vec3(0, 1, 0));

		Renderer::GetUBOPojectionView()[0].SetMat4("View", glm::mat4(glm::mat3(view)));

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