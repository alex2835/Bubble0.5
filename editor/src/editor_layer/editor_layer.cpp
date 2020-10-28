
#include "editor_layer.h"


namespace Bubble
{
	EditorLayer::EditorLayer()
		: mSceneCamera(glm::vec3(0.0f, 5.0f, 0.0f))
	{}

	void EditorLayer::OnAttach()
	{
        mImGuiControll.OnAttach();

        // Temp: test viewport
		mViewport = Viewport(800, 800);

		// ============ Model entities =============
	
		OpenProject("../../../../scene_test.json", &mScene);

		// Temp: skybox
		mActiveSkybox = CreateRef<Skybox>("resources/skybox/skybox1.jpg");
		mSkyboxShader = Shader::Open("resources/shaders/skybox.glsl");

		mPhongShader = Shader::Open("resources/shaders/phong.glsl");
		mSelectedItemShader = Shader::Open("resources/shaders/solid_color.glsl");

		// Temp: Try to simplify mesh
 	}


	void EditorLayer::OnDetach()
	{
        mImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// Set args for UI
		mUI.Args = { &mImGuiControll, &mSceneCamera, &mViewport, &mScene };
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
				lc.light.SetDistance();
				Light::ApplyLight(lc.light, mPhongShader, light_index++);
			}
		);
		mPhongShader->SetUni1i("nLights", light_index);


		// Temp: Draw scene
		glm::ivec2 window_size = mViewport.GetSize();
		glm::mat4 projection = mSceneCamera.GetPprojectionMat(window_size.x, window_size.y);
		glm::mat4 view = mSceneCamera.GetLookatMat();

		mPhongShader->SetUniMat4("u_View", view);
		mPhongShader->SetUniMat4("u_Projection", projection);

		auto scene_view = mScene.GetView<ModelComponent, TransformComponent>();

		for (auto entity : scene_view)
		{
			auto& [mesh, model] = scene_view.get<ModelComponent, TransformComponent>(entity);
			mPhongShader->SetUniMat4("u_Model", model);
			Renderer::DrawModel(mesh, mPhongShader, mUI.DrawTypeOption);
		}

		// Highlight selected model
		{
			Entity selected_entity = mUI.SceneExplorerPanel.SelectedEntity;

			if (selected_entity.Valid() && selected_entity.HasComponent<ModelComponent, TransformComponent>())
			{
				auto& [mesh, model] = selected_entity.GetComponent<ModelComponent, TransformComponent>();

				glDisable(GL_DEPTH_TEST);
				mSelectedItemShader->SetUni4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
				mSelectedItemShader->SetUniMat4("u_Transforms", projection * view * (glm::mat4)model);
				Renderer::DrawModelA(mesh, mSelectedItemShader, DrawType::TRIANGLES);
				glEnable(GL_DEPTH_TEST);
			}
		}

		// Render skybox
		view = glm::rotate(view, glm::radians(Application::GetTime() * 0.5f), glm::vec3(0, 1, 0));
		mSkyboxShader->SetUniMat4("u_Projection", projection);
		mSkyboxShader->SetUniMat4("u_View", glm::mat3(view));
		mSkyboxShader->SetUni1f("u_Brightness", 1.0f);
		Renderer::DrawSkybox(mActiveSkybox, mSkyboxShader);

	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mImGuiControll.OnEvent(event);

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Application::GetWindow()->Close();
		}
	}

}