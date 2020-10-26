
#include "editor_layer.h"


namespace Bubble
{
	EditorLayer::EditorLayer()
		: SceneCamera(glm::vec3(0.0f, 5.0f, 0.0f))
	{}

	void EditorLayer::OnAttach()
	{
        ImGuiControll.OnAttach();

        // Temp: test viewport
		MainViewport = Viewport(800, 800);

		// ============ Model entities =============
	
		OpenProject("../../../../scene_test.json", &ActiveScene);

		// Temp: skybox
		ActiveSkybox = CreateRef<Skybox>("resources/skybox/skybox1.jpg");
		SkyboxShader = Shader::Open("resources/shaders/skybox.glsl");

		PhongShader = Shader::Open("resources/shaders/phong.glsl");
		SelectedItemShader = Shader::Open("resources/shaders/solid_color.glsl");

		// Temp: Try to simplify mesh
	}


	void EditorLayer::OnDetach()
	{
        ImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// Set args for UI
		UserInterface.Args = { &ImGuiControll, &SceneCamera, &MainViewport, &ActiveScene };
		// User Interface
		UserInterface.Draw(dt);


		// Scene camera update
		SceneCamera.OnUpdate(dt);


		Renderer::SetViewport(MainViewport);
		Renderer::ClearDepth();

		// Temp : Apply lights to shader
		int light_index = 0;
		ActiveScene.Registry.view<LightComponent>().each(
			[&](auto entity, LightComponent& lc)
			{
				lc.light.SetDistance();
				Light::ApplyLight(lc.light, PhongShader, light_index++);
			}
		);
		PhongShader->SetUni1i("nLights", light_index);


		// Temp: Draw scene
		glm::ivec2 window_size = MainViewport.GetSize();
		glm::mat4 projection = SceneCamera.GetPprojectionMat(window_size.x, window_size.y);
		glm::mat4 view = SceneCamera.GetLookatMat();

		PhongShader->SetUniMat4("u_View", view);
		PhongShader->SetUniMat4("u_Projection", projection);

		auto scene_view = ActiveScene.GetView<ModelComponent, TransformComponent>();

		for (auto entity : scene_view)
		{
			auto& [mesh, model] = scene_view.get<ModelComponent, TransformComponent>(entity);
			PhongShader->SetUniMat4("u_Model", model);
			Renderer::DrawModel(mesh, PhongShader, UserInterface.DrawTypeOption);
		}

		// Highlight selected model
		{
			Entity selected_entity = UserInterface.SceneExplorerPanel.SelectedEntity;

			if (selected_entity.Valid() && selected_entity.HasComponent<ModelComponent, TransformComponent>())
			{
				auto& [mesh, model] = selected_entity.GetComponent<ModelComponent, TransformComponent>();

				glDisable(GL_DEPTH_TEST);
				SelectedItemShader->SetUni4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
				SelectedItemShader->SetUniMat4("u_Transforms", projection * view * (glm::mat4)model);
				Renderer::DrawModelA(mesh, SelectedItemShader, DrawType::TRIANGLES);
				glEnable(GL_DEPTH_TEST);
			}
		}

		// Render skybox
		view = glm::rotate(view, glm::radians(Application::GetTime() * 0.5f), glm::vec3(0, 1, 0));
		SkyboxShader->SetUniMat4("u_Projection", projection);
		SkyboxShader->SetUniMat4("u_View", glm::mat3(view));
		SkyboxShader->SetUni1f("u_Brightness", 1.0f);
		Renderer::DrawSkybox(ActiveSkybox, SkyboxShader);

	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        ImGuiControll.OnEvent(event);

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Application::GetWindow()->Close();
		}
	}

}