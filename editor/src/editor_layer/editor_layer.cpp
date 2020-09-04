
#include "editor_layer.h"


namespace Bubble
{
    EditorLayer::EditorLayer() {}

	void EditorLayer::OnAttach()
	{
        m_ImGuiControll.OnAttach();

        // Temp: test viewport
		m_ViewportArray.Push(Viewport(800, 800));

		// Temp: Draw stuff
		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		m_VertexArray = CreateRef<VertexArray>();
		m_VertexBuffer = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
		
		BufferLayout layout = {
			{ GLSLDataType::Float3, "a_Position" },
			{ GLSLDataType::Float2, "a_TexCoords" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0};
		m_IndexBuffer = CreateRef<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Texture = CreateRef<Texture2D>("resources/bubble.jpg");

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			
			out vec3 v_Position;
			out vec2 v_TexCoord;
			
			void main()
			{
				v_Position = a_Position;
				v_TexCoord = a_TexCoord;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader = CreateScope<Shader>("Test shader", vertexSrc, fragmentSrc);
		
		m_ShaderPhong = CreateRef<Shader>("C:\\Users\\lol\\Desktop\\bubble\\engine\\src\\content\\shaders\\phong.glsl");
		m_NanoSuit = ModelLoader::StaticModel("resources/crysis/nanosuit.obj");

		// Temp: Scene
		m_Scene = CreateRef<Scene>();
		m_Entity = m_Scene->CreateEntity("TestEntity");
	}


	void EditorLayer::OnDetach()
	{
        m_ImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		Framebuffer::BindDefault();
		m_ImGuiControll.Begin();

        // Temp: Veiwports control
		m_ViewportArray.RemoveNotActiveViewports();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		for (int i = 0; i < m_ViewportArray.Size(); i++)
		{
			ImGui::Begin(m_ViewportArray[i].GetName().c_str(), (bool*)&m_ViewportArray.IsOpen(i));

			ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
			glm::vec2 viewport_size = m_ViewportArray[i].Size();

			if (viewport_size != *(glm::vec2*) & imgui_viewport_size)
				m_ViewportArray[i].Resize({ imgui_viewport_size.x, imgui_viewport_size.y });

			uint32_t textureId = m_ViewportArray[i].GetFramebuffer().GetColorAttachmentRendererID();

			ImGui::Image((void*)textureId, ImVec2{ (float)m_ViewportArray[i].Size().x, (float)m_ViewportArray[i].Size().y });
			ImGui::End();
		}
		ImGui::PopStyleVar();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow();
        m_ImGuiControll.End();


		// Scene update
		m_Scene->OnUpdate(dt);

		// Scene camera update
		m_SceneCamera.OnUpdate(dt);

		// Temp: Test image
		Renderer::SetViewport(m_ViewportArray[0].GetFramebuffer());
		Renderer::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Renderer::Clear();

		m_Shader->Bind();

		m_Texture->Bind();
		m_Shader->SetUni1i("u_Texture", 0);

		Renderer::DrawIndex(m_VertexArray);



	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        m_ImGuiControll.OnEvent(event);
	}

}