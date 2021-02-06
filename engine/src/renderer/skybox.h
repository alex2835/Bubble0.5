#pragma once

#include "cubemap.h"
#include "vertex_array.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"


namespace Bubble
{
	struct Skybox
	{
		static VertexArray* SkyboxVertexArray;
		static void InitVertexArray();

		Cubemap mSkybox;

		Skybox() = default;

		Skybox(const Skybox&) = delete;
		Skybox& operator=(const Skybox&) = delete;

		Skybox(Skybox&&) = default;
		Skybox& operator=(Skybox&&) = default;

		void Bind(int slot = 0);
		
		// Generate matrix for correct skybox rendering
		static glm::mat4 GetViewMatrix(glm::mat4 view, float rotation = 0);
	};
}