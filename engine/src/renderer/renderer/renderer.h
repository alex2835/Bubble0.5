
#include "renderer_base.h"
#include "vertex_array/vertex_array.h"
#include "framebuffer/framebuffer.h"
#include "glm/glm.hpp"


namespace Bubble
{
	enum class DrawType { LINES, TRIANGLES };

	class Renderer
	{
	public:
		static void Init();

		static void SetViewport(const Framebuffer& framebuffer, uint32_t x = 0, uint32_t y = 0, uint32_t width = 0, uint32_t height = 0);

		static void SetClearColor(const glm::vec4& color);

		static void Clear();

		static void DrawIndex(const Ref<VertexArray>& vertexArray, DrawType draw_type = DrawType::TRIANGLES, uint32_t count = 0);
	};
}