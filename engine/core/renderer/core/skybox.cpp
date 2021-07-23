
#include "skybox.h"

namespace Bubble
{
	void Skybox::Bind(const Ref<VertexArray>& vertex_array, int slot)
	{
		vertex_array->Bind();
		mSkybox.Bind(slot);
	}


	glm::mat4 Skybox::GetViewMatrix(glm::mat4 view, float rotation)
	{
		view = glm::rotate(view, rotation, glm::vec3(0, 1, 0));
		view = glm::mat4(glm::mat3(view));
		return view;
	}

}

