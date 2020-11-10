
#include "draw_selected_entity.h"


namespace Bubble
{
	static Ref<Shader> SelectedModelShader;

	void draw_selected_model(Entity selected_entity)
	{
		if (SelectedModelShader == nullptr)
		{
			SelectedModelShader = ShaderLoader::Load("resources/shaders/solid_color.glsl");
		}

		if (selected_entity.Valid() && selected_entity.HasComponent<ModelComponent, TransformComponent>())
		{
			SelectedModelShader->SetUni4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 0.05f));

			auto& [model, transforms] = selected_entity.GetComponent<ModelComponent, TransformComponent>();
			Renderer::DepthTest(false);
			Renderer::DrawModelA(model, transforms, SelectedModelShader);
			Renderer::DepthTest(true);
		}
	}

}


