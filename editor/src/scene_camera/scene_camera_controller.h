#pragma once

#include "camera/camera.h"
#include "delta_time/delta_time.h"

namespace Bubble
{
	class SceneCameraController
	{
		Camera m_Camera;

	public:
		void OnUpdate(DeltaTime dt);

		glm::mat4 GetLookatMat();
		glm::mat4 GetPprojectionMat(int WindowWidth, int WindowHeight, float near = 0.1f, float far = 120.0f);
	};
}