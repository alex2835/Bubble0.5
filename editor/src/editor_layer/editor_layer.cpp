
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
		ViewportArray.Push(Viewport(800, 800));

		ActiveScene = CreateRef<Scene>();

		// ============ Model entities =============
		Entities.push_back(ActiveScene->CreateEntity("nanosuit")
			.AddComponent<Ref<Model>>(ModelLoader::StaticModel("resources/crysis/nanosuit.obj"))
			.AddComponent<TransformComponent>()
			.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, -10.0f))
			.AddComponent<RotationComponent>()
			.AddComponent<ScaleComponent>(glm::vec3(0.7f))
		);
		
		Entities.push_back(ActiveScene->CreateEntity("grass")
			.AddComponent<Ref<Model>>(ModelLoader::StaticModel("resources/grass_plane/grass_plane.obj"))
			.AddComponent<TransformComponent>()
			.AddComponent<PositionComponent>(glm::vec3(0.0f, -7.0f, 0.0f))
			.AddComponent<RotationComponent>(glm::vec3(glm::radians(-90.0f), 0, 0))
			.AddComponent<ScaleComponent>(glm::vec3(0.3f))
		);
		
		Entities.push_back(ActiveScene->CreateEntity("tree")
			.AddComponent<Ref<Model>>(ModelLoader::StaticModel("resources/Tree/Tree.obj"))
			.AddComponent<TransformComponent>()
			.AddComponent<PositionComponent>(glm::vec3(10.0f, 1.0f, 0.0f))
			.AddComponent<RotationComponent>()
			.AddComponent<ScaleComponent>(glm::vec3(5.0f))
		);

		// Hard code
		for (auto entity = Entities.end() - 3; entity < Entities.end(); entity++)
		{
			auto& transform = entity->GetComponent<TransformComponent>().Transform;
			auto& position = entity->GetComponent<PositionComponent>().Position;
			auto& rotation = entity->GetComponent<RotationComponent>().Rotation;
			auto& scale = entity->GetComponent<ScaleComponent>().Scale;
		
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, position);
			transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
			transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
			transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
			transform = glm::scale(transform, scale);
		}


		Entities.push_back(ActiveScene->CreateEntity("DirLight")
			.AddComponent<LightComponent>(Light::CreateDirLight(glm::vec3(0.1f, -1.0f, -1.0f))));

		Entities.push_back(ActiveScene->CreateEntity("SpotLight")
			.AddComponent<LightComponent>(Light::CreateSpotLight()));

		Entities.push_back(ActiveScene->CreateEntity("PointLight")
			.AddComponent<LightComponent>(Light::CreatePointLight(glm::vec3(3.0f, 5.0f, 0.0f))));

		// Temp: skybox
		m_Skybox = CreateRef<Skybox>("resources/skybox/skybox1.jpg");
		m_ShaderSkybox = Shader::Open("resources/shaders/skybox.glsl");

		m_ShaderPhong = Shader::Open("resources/shaders/phong.glsl");
		ShaderSelected = Shader::Open("resources/shaders/solid_color.glsl");


		// Temp: Serialization
		std::stringstream storage;

		entt::registry source;
		entt::registry destination;

		auto e0 = source.create();
		source.emplace<PositionComponent>(e0, glm::vec3{ 16.f, 16.f, 1.0f } );

		source.destroy(source.create());

		auto e1 = source.create();
		source.emplace<PositionComponent>(e1, glm::vec3{.8f, .0f, 1.0f} );
		source.emplace<RotationComponent>(e1, glm::vec3{2.8f, 2.0f, 2.0f} );
		//source.emplace<relationship>(e1, e0);

		//{
		//	// output finishes flushing its contents when it goes out of scope
		//	//cereal::JSONOutputArchive output{ storage };
		//	output_archive output;
		//	entt::snapshot{ source }.entities(output).component<PositionComponent, RotationComponent>(output);
		//	nlohmann::json j1 = output.j["Components"][0];
		//	LOG_INFO(output.j.dump());
		//	LOG_INFO(j1.dump());
		//
		//	input_archive input{output.j};
		//
		//	//cereal::JSONInputArchive input{ storage };
		//	entt::snapshot_loader{ destination }.entities(input).component<PositionComponent, RotationComponent>(input);
 		//}


		SaveProject("test.json", source);
		


		// Temp: Try to simplify mesh
	}


	void EditorLayer::OnDetach()
	{
        ImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// Set args for UI
		UserInterface.Args = { &Models, &SceneCamera, ActiveScene.get() };

		// ImGui Scope
		ImGuiControll.Begin();

		// MenuBar
		ImGuiControll.BeginMenuBar();
		DrawMenuBar();
		ImGuiControll.EndMenuBar();

		// User Interface
		UserInterface.Draw();

        // Temp: Veiwports control
		ViewportArray.RemoveNotActiveViewports();
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		for (int i = 0; i < ViewportArray.Size(); i++)
		{
			ImGui::Begin(ViewportArray[i].GetName().c_str(), (bool*)&ViewportArray.IsOpen(i));

			ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
			glm::vec2 viewport_size = ViewportArray[i].Size();

			if (viewport_size != *(glm::vec2*) & imgui_viewport_size) {
				ViewportArray[i].Resize({ imgui_viewport_size.x, imgui_viewport_size.y });
			}

			uint32_t textureId = ViewportArray[i].GetFramebuffer().GetColorAttachmentRendererID();

			ImGui::Image((void*)textureId, ImVec2{ (float)ViewportArray[i].Size().x, (float)ViewportArray[i].Size().y }, ImVec2(1, 1), ImVec2(0, 0));
			ImGui::End();
		}
		ImGui::PopStyleVar();

		
		ImGui::Begin("Info");
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		// DemoWindow
		ImGui::ShowDemoWindow();

        ImGuiControll.End();


		// ActiveScene update
		ActiveScene->OnUpdate(dt);

		// ActiveScene camera update
		SceneCamera.OnUpdate(dt);

		Renderer::SetViewport(ViewportArray[0].GetFramebuffer());
		Renderer::ClearDepth();

		m_Lights.ApplyLights(m_ShaderPhong);

		// Temp : Apply lights to shader
		int light_index = 0;
		ActiveScene->m_Registry.view<LightComponent>().each(
			[&] (auto entity, LightComponent& lc)
			{
				lc.light.SetDistance();
				Light::ApplyLight(lc.light, m_ShaderPhong, light_index++);
			}
		);
		m_ShaderPhong->SetUni1i("nLights", light_index);


		// Temp: Draw test mesh
		glm::ivec2 window_size = ViewportArray[0].Size();
		glm::mat4 projection = SceneCamera.GetPprojectionMat(window_size.x, window_size.y);
		glm::mat4 view = SceneCamera.GetLookatMat();
		
		m_ShaderPhong->SetUniMat4("u_View", view);
		m_ShaderPhong->SetUniMat4("u_Projection", projection);

		auto scene_view = ActiveScene->GetView<Ref<Model>, TransformComponent>();

		for (auto entity : scene_view)
		{
			auto [mesh, model] = scene_view.get<Ref<Model>, TransformComponent>(entity);
			m_ShaderPhong->SetUniMat4("u_Model", model);
			Renderer::DrawModel(mesh, m_ShaderPhong, UserInterface.DrawTypeOption);

			// Hightlight selected model
			if (UserInterface.SceneExplorerPanel.SelectedEntity == entity)
			{
				glDisable(GL_DEPTH_TEST);
				ShaderSelected->SetUni4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
				ShaderSelected->SetUniMat4("u_Transforms", projection * view * (glm::mat4)model);
				Renderer::DrawModelA(mesh, ShaderSelected, DrawType::TRIANGLES);
				glEnable(GL_DEPTH_TEST);
			}
		}

		// Render skybox
		m_ShaderSkybox->SetUniMat4("u_Projection", projection);
		view = glm::rotate(view, glm::radians(Application::GetTime() * 0.5f), glm::vec3(0, 1, 0));
		m_ShaderSkybox->SetUniMat4("u_View", glm::mat3(view));
		m_ShaderSkybox->SetUni1f("u_Brightness", 1.0f);
		Renderer::DrawSkybox(m_Skybox, m_ShaderSkybox);

	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        ImGuiControll.OnEvent(event);

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Application::GetWindow()->Close();
		}
	}

	void EditorLayer::DrawMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			// ====== Editor Menu ======
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
					try
					{
						std::string path = OpenFileDialog("json");
						OpenProject(path, ActiveScene->m_Registry);
					}
					catch (const std::exception& e)
					{
						LOG_ERROR(e.what());
					}
				}

				if (ImGui::MenuItem("Save"))
				{
					SaveProject("scene_test.json", ActiveScene->m_Registry);
				}

				ImGui::EndMenu();
			}

			// ====== UI Menu =======
			UserInterface.DrawMenu();

			ImGui::EndMenuBar();
		}
	}

}