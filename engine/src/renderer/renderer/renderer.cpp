
#include "renderer.h"


namespace Bubble
{
	void Renderer::Init()
	{
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::SetViewport(const Framebuffer& framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		framebuffer.Bind();
		if (width * height)
		{
			glViewport(x, y, width, height);
		}
		else
		{
			glViewport(0, 0, framebuffer.GetWidth(), framebuffer.GetHeight());
		}
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawIndexed(const Ref<VertexArray>& vertex_array, DrawType draw_type, uint32_t index_count)
	{
		vertex_array->Bind();
		uint32_t opengl_draw_type = 0;
		switch (draw_type)
		{
			case DrawType::LINES:
				opengl_draw_type = GL_LINES;
				break;
			case DrawType::TRIANGLES:
				opengl_draw_type = GL_TRIANGLES;
				break;
			default:
				BUBBLE_CORE_ASSERT(false, "Unknown draw type");
		}
		uint32_t count = index_count ? index_count : vertex_array->GetIndexBuffer()->GetCount();
		glcall(glDrawElements(opengl_draw_type, count, GL_UNSIGNED_INT, nullptr));
	}
}