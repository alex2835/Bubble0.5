#pragma once

#include "core/input.h"
#include "core/time.h"
#include "renderer/camera_free.h"

#include "SDL2/SDL.h"

namespace Bubble
{
	struct SceneCamera : public FreeCamera
	{
		float BoostSpeed = 5.0f;

		SceneCamera(const glm::vec3& position = glm::vec3(0.0f));
		void Update(DeltaTime dt);
	};

}