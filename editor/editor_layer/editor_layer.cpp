
#include "editor_layer.h"

namespace Bubble
{
    EditorLayer::EditorLayer(SDL_WINDOW* window)
        : m_ImGuiControll(window)
    {}

	void EditorLayer::OnAttach()
	{
        m_ImGuiControll.OnAttach();

        // Temp: test viewport
		m_ViewportArray.Push(Viewport(200, 100));

		// Temp: Draw stuff

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexArray = CreateScope<VertexArray>();
		m_VertexBuffer = CreateRef<VertexBuffer>(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ GLSLDataType::Float3, "a_Position" },
			{ GLSLDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer = CreateRef<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = CreateScope<Shader>(vertexSrc, fragmentSrc);

	}

	void EditorLayer::OnDetach()
	{
        m_ImGuiControll.OnDetach();
	}
	
	void EditorLayer::OnUpdate()
	{
        // Temp: Test triangle draw

		m_ViewportArray[0].Bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader->Bind();
		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		m_ViewportArray[0].Unbind();



		m_ImGuiControll.Begin();

        // Temp: Veiwports control
		m_ViewportArray.RemoveNotActiveViewports();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		for (int i = 0; i < m_ViewportArray.Size(); i++)
		{
			ImGui::Begin(m_ViewportArray[i].GetName().c_str(), (bool*)&m_ViewportArray.IsOpen(i));

			ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
			glm::vec2 fViewportSize = m_ViewportArray[i].Size();
			if (fViewportSize != *(glm::vec2*) & imgui_viewport_size)
			{
				m_ViewportArray[i].Resize({ imgui_viewport_size.x, imgui_viewport_size.y });
			}
			uint32_t textureId = m_ViewportArray[i].GetFramebuffer().GetColorAttachmentRendererID();

			ImGui::Image((void*)textureId, ImVec2{ (float)m_ViewportArray[i].Size().x, (float)m_ViewportArray[i].Size().y });
			ImGui::End();
		}
		ImGui::PopStyleVar();


        // Temp: fill screen color
        //for (auto& viewport : m_ViewportArray)
        //{
        //    viewport.Bind();
        //    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        //    glClear(GL_COLOR_BUFFER_BIT);
        //    viewport.Unbind();
        //}

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();
        }

        // Temp: 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        m_ImGuiControll.End();
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        // Temp: add viewport by pressing space
		if (event.type == SDL_EventType::SDL_KEYDOWN
			&& event.key.keysym.sym == SDLK_SPACE)
			m_ViewportArray.Push(Viewport(200, 200));

        m_ImGuiControll.OnEvent(event);
	}

}