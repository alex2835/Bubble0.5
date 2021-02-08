#pragma once

#include "engine.h"

namespace Bubble
{
	struct SceneCamera : public FreeCamera
	{
		float BoostSpeed = 5.0f;

		SceneCamera(const glm::vec3& position = glm::vec3(0.0f));
		void Update(DeltaTime dt);
	};

}