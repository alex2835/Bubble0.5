
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
	}

	void EditorLayer::OnDetach()
	{
        m_ImGuiControll.OnDetach();
	}
	
	void EditorLayer::OnUpdate()
	{
        // test triangle draw
        
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		static int preapare_flag = 1;

		static uint32_t vertex_array = 0;

			if (vertex_array == 0)
			{
				glGenVertexArrays(1, &vertex_array);
				glBindVertexArray(vertex_array);
			}

			static VertexBuffer vertex_buffer(vertices, sizeof(vertices));

			{
				BufferLayout layout = {
					{ GLSLDataType::Float3, "a_Position" },
					{ GLSLDataType::Float4, "a_Color" }
				};

				vertex_buffer.SetLayout(layout);
			}


			if (preapare_flag)
			{
				glBindVertexArray(vertex_array);
				preapare_flag = 0;

				uint32_t index = 0;
				const auto& layout = vertex_buffer.GetLayout();
				for (const auto& element : layout)
				{
					glcall(glEnableVertexAttribArray(index));
 					glcall(glVertexAttribPointer(index,
						element.GetComponentCount(),
						GLSLDataTypeToOpenGLBaseType(element.m_Type),
						element.m_Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.m_Offset));
					index++;
				}
			}

			uint32_t indices[3] = { 0, 1, 2 };
			static IndexBuffer index_buffer(indices, sizeof(indices) / sizeof(uint32_t));

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

		static Shader shader(vertexSrc, fragmentSrc);

		m_ViewportArray[0].Bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		glBindVertexArray(vertex_array);
		glDrawElements(GL_TRIANGLES, index_buffer.GetCount(), GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		m_ViewportArray[0].Unbind();


		m_ImGuiControll.Begin();

        // Temp: Veiwports control
		m_ViewportArray.RemoveNotActiveViewports();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		for (int i = 0; i < m_ViewportArray.Size(); i++)
		{
			bool isOpen = m_ViewportArray.m_IsOpen[i];
			ImGui::Begin(m_ViewportArray[i].GetName().c_str(), &isOpen);
            m_ViewportArray.m_IsOpen[i] = isOpen;

			ImVec2 imguiViewportSize = ImGui::GetContentRegionAvail();
			glm::vec2 ViewportSize = m_ViewportArray[i].Size();
			if (ViewportSize != *(glm::vec2*) & imguiViewportSize)
                m_ViewportArray[i].Resize({ imguiViewportSize.x, imguiViewportSize.y });

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