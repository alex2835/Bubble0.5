#pragma once

#include "camera.h"


namespace Bubble
{
	struct FreeCamera : public Camera
	{
		float LastMouseX = 0.5f;
		float LastMouseY = 0.5f;

		bool IsMovingX = false;
		bool IsMovingY = false;

		FreeCamera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
				   float yaw = YAW,
				   float pitch = PITCH,
				   float fov = FOV,
				   const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)
		);

		void ProcessMovement(CameraMovement direction, DeltaTime dt);
		void ProcessMouseMovement(float xMousePos, float yMousePos);
		void ProcessMouseMovementShift(float xoffset, float yoffset);
		void ProcessMouseScroll(float yoffset);

		void Update(DeltaTime dt);
	};
}
