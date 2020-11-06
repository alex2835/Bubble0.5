
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

		BufferLayout UBOProjectionViewLayout{
			{ GLSLDataType::Mat4, "Projection" },
			{ GLSLDataType::Mat4, "View" }
		};
		mUBOPrjectionview = UniformBuffer(0, UBOProjectionViewLayout);

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

		// Fill ubo
		glm::mat4 PrjView[2] = { projection, view };
		mUBOPrjectionview.SetData(&PrjView, sizeof(PrjView));


		SetFrustumPlanes(projection * view);

		// Draw scene
		auto scene_view = mScene.GetView<ModelComponent, TransformComponent>();
		for (auto entity : scene_view)
		{
			auto& [mesh, model] = scene_view.get<ModelComponent, TransformComponent>(entity);

			if (IsInFrustum(mesh.mModel->mBoundingBox.transform(model)))
			{
				mPhongShader->SetUniMat4("u_Model", model);
				Renderer::DrawModel(mesh, mPhongShader);
			}
		}


		// ======================= Draw editor sruff =======================

		// Highlight selected entity
		draw_selected_model(mUI.mSceneExplorer.SelectedEntity, projection * view);
		

		// Draw boundingBox
		if (mUI.mBoundingBoxOption)
		{
			for (auto entity : scene_view)
			{
				auto& [mesh, model] = scene_view.get<ModelComponent, TransformComponent>(entity);
				draw_boundingbox(((Ref<Model>)mesh)->mBoundingBox.transform(model), projection * view);
			}
		}


		// ========================= Draw skybox ========================= 

		view = glm::rotate(view, glm::radians(Timer::GetTime().GetSeconds() * 0.5f), glm::vec3(0, 1, 0));
		mUBOPrjectionview[0].SetMat4("View", glm::mat4(glm::mat3(view)));
		mSkyboxShader->SetUni1f("u_Brightness", 1.0f);
		Renderer::DrawSkybox(mActiveSkybox, mSkyboxShader);

	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mImGuiControll.OnEvent(event);

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			Application::GetWindow()->Close();
		}
	}

}