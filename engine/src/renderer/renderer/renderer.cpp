
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
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
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


	void Renderer::DrawIndex(const Ref<VertexArray>& vertex_array, DrawType draw_type, uint32_t index_count)
	{
		vertex_array->Bind();
		uint32_t count = index_count ? index_count : vertex_array->GetIndexBuffer()->GetCount();
		glcall(glDrawElements(OpenGLDrawType(draw_type), count, GL_UNSIGNED_INT, nullptr));
	}


	void Renderer::DrawMesh(const Ref<Mesh>& mesh, const Ref<Shader>& shader, DrawType draw_type)
	{
		// bind appropriate textures
		uint32_t diffuseNr = 1;
		uint32_t specularNr = 1;
		uint32_t normalNr = 1;
		uint32_t heightNr = 1;

		int index = 0;
		for (const MeshTexture& texture : mesh->GetTextures())
		{
			shader->ActivateTexture(index);
			
			int number;
			TextureType type = texture.type;
			if (type == TextureType::DIFFUSE) {
				number = diffuseNr++;
			}
			else if (type == TextureType::SPECULAR) {
				number = specularNr++;
			}
			else if (type == TextureType::NORMAL) {
				number = normalNr++;
			}
			else if (type == TextureType::HEIGHT) {
				number = heightNr++;
			}
			else {
				BUBBLE_CORE_ASSERT(false, "Invalid texture type");
			}
		
			shader->SetUni1i(texture_type_names[(int)type] + std::to_string(number), index);
			texture.Bind();
		}
		
		// Temp
		shader->SetUni1i("material.shininess", mesh->shininess);
		
		// draw mesh
		mesh->VertexArray.Bind();
		glDrawElements(OpenGLDrawType(draw_type), mesh->Indices->size(), GL_UNSIGNED_INT, 0);
		
		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

}