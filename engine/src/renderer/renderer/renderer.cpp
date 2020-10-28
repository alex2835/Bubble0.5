
#include "renderer.h"


namespace Bubble
{
	static uint32_t OpenGLDrawType(DrawType draw_type)
	{
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
		return opengl_draw_type;
	}


	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}


	void Renderer::SetViewport(const Framebuffer& framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		framebuffer.Bind();
		if (width * height) {
			glViewport(x, y, width, height);
		}
		else {
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


	void Renderer::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawIndex(const Ref<VertexArray>& vertex_array, DrawType draw_type, uint32_t index_count)
	{
		vertex_array->Bind();
		uint32_t count = index_count ? index_count : vertex_array->GetIndexBuffer().GetCount();
		glcall(glDrawElements(OpenGLDrawType(draw_type), count, GL_UNSIGNED_INT, nullptr));
	}


	void Renderer::DrawMesh(const Ref<Mesh>& mesh, const Ref<Shader>& shader, DrawType draw_type)
	{
		Renderer::DrawMesh(*mesh.get(), shader, draw_type);
	}

	void Renderer::DrawMesh(const Mesh& mesh, const Ref<Shader>& shader, DrawType draw_type)
	{
		mesh.mVertexArray.Bind();
		mesh.mMaterial.Set(shader);
		glDrawElements(OpenGLDrawType(draw_type), mesh.mIndices.size(), GL_UNSIGNED_INT, 0);
		Texture2D::UnbindAll();
	}

	void Renderer::DrawModel(const Ref<Model>& model, const Ref<Shader>& shader, DrawType draw_type)
	{
		for (const auto& mesh : model->mMeshes)
		{
			Renderer::DrawMesh(mesh, shader, draw_type);
		}
	}

	void Renderer::DrawModelA(const Ref<Model>& model, const Ref<Shader>& shader, DrawType draw_type)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (const auto& mesh : model->mMeshes)
		{
			Renderer::DrawMesh(mesh, shader, draw_type);
		}

		glDisable(GL_BLEND);
	}

	void Renderer::DrawAABB(const AABB& aabb)
	{
		//static glBert
		//glDrawBuffer();
	}

	void Renderer::DrawSkybox(const Ref<Skybox>& skybox, const Ref<Shader>& shader)
	{
		shader->Bind();
		skybox->Bind();
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);
	}

}