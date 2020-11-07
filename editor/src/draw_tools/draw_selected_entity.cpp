
#include "draw_selected_entity.h"


namespace Bubble
{
	static Ref<Shader> sSelectedModelShader;

	void draw_selected_model(Entity selected_entity)
	{
		if (sSelectedModelShader == nullptr)
		{
			sSelectedModelShader = ShaderLoader::Load("resources/shaders/solid_color.glsl");
		}

		if (selected_entity.Valid() && selected_entity.HasComponent<ModelComponent, TransformComponent>())
		{
			auto& [mesh, model] = selected_entity.GetComponent<ModelComponent, TransformComponent>();
			glDisable(GL_DEPTH_TEST);
			sSelectedModelShader->SetUni4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
			Renderer::DrawModelA(mesh, model, sSelectedModelShader);
			glEnable(GL_DEPTH_TEST);
		}
	}

}


