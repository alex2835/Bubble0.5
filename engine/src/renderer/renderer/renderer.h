#pragma once

#include "renderer_base.h"
#include "vertex_array/vertex_array.h"
#include "framebuffer/framebuffer.h"
#include "shader/shader.h"
#include "model/model.h"
#include "skybox/skybox.h"
#include "scene.h"
#include "buffer/buffer.h"

#include "glm/glm.hpp"
#include "glm-AABB/AABB.hpp"


namespace Bubble
{
	enum class DrawType { POINTS, LINES, TRIANGLES };

	class Renderer
	{
	public:
		static void Init();

		// Options
		static void Wareframe(bool);
		static void AlphaBlending(bool);
		static void BackfaceCulling(bool);
		static void DepthTest(bool);

		static void SetViewport(const Framebuffer& framebuffer, uint32_t x = 0, uint32_t y = 0, uint32_t width = 0, uint32_t height = 0);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void ClearDepth();
		static void ClearColor();

		static void DrawIndex(const Ref<VertexArray>& vertexArray, DrawType draw_type = DrawType::TRIANGLES, uint32_t count = 0);
		static void DrawMesh(const Mesh& mesh, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);
		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);
		static void DrawModel(const Ref<Model>& model, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);
		static void DrawModelA(const Ref<Model>& model, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);
		static void DrawSkybox(const Ref<Skybox>& model, const Ref<Shader>& shader);

		static void DrawScene(const Scene& scene);
	};
}