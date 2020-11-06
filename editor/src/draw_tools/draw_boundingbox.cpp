

#include "draw_boundingbox.h"


namespace Bubble
{
	static Ref<Shader> sBoundingBoxShader;
	static Ref<VertexArray> sVertexArray;


	static void init_bounding_box_drawing()
	{
		sBoundingBoxShader = ShaderLoader::Load("resources/shaders/solid_color.glsl");
		sVertexArray = CreateRef<VertexArray>();

		uint32_t indices[] = {4, 0, 0, 2, 2, 7, 7, 4,
							  0, 3, 2, 5, 7, 1, 4, 6, 
							  6, 3, 3, 5, 5, 1, 1, 6};

		IndexBuffer ib(indices, sizeof(indices) / sizeof(uint32_t));
		VertexBuffer vb(8 * 4 * 3);

		BufferLayout layout{
			{GLSLDataType::Float3, "Position" }
		};

		vb.SetLayout(layout);
		sVertexArray->AddVertexBuffer(std::move(vb));
		sVertexArray->SetIndexBuffer(std::move(ib));
	}


	void draw_boundingbox(const AABB& bb)
	{
		if (sBoundingBoxShader == nullptr)
		{
			init_bounding_box_drawing();
		}
		sBoundingBoxShader->SetUni4f("u_Color", glm::vec4(1.0f));
		sBoundingBoxShader->SetUniMat4("u_Model", glm::mat4(1.0f));
		{
			glm::vec3 min = bb.getMin();
			glm::vec3 max = bb.getMax();

			glm::vec3 pos[] = { min, max,
				glm::vec3(max.x, min.y, min.z),
				glm::vec3(min.x, max.y, min.z),
				glm::vec3(min.x, min.y, max.z),
				glm::vec3(max.x, max.y, min.z),
				glm::vec3(min.x, max.y, max.z),
				glm::vec3(max.x, min.y, max.z)
			};
			sVertexArray->GetVertexBuffers()[0].SetData(pos, sizeof(pos));

			Renderer::BackfaceCulling(false);
			Renderer::DrawIndex(sVertexArray, DrawType::LINES);
			Renderer::BackfaceCulling(true);
		}
	}

	void draw_scene_boundingbox(Scene& scene)
	{
		auto scene_view = scene.GetView<ModelComponent, TransformComponent>();

		// Draw boundingBoxes
		for (auto entity : scene_view)
		{
			auto& [mesh, model] = scene_view.get<ModelComponent, TransformComponent>(entity);
			draw_boundingbox(((Ref<Model>)mesh)->mBoundingBox.transform(model));
		}
	}

}