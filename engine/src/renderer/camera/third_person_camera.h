#pragma once

#include "camera.h"
#include <glm/glm.hpp>


namespace Bubble
{
	struct ThirdPersonCamera : public Camera
	{
		glm::vec3 Center;
		float Radius = 20.0f;

		float LastMouseX = 0.5f;
		float LastMouseY = 0.5f;

		bool IsRotatingX = false;
		bool IsRotatingY = false;

		ThirdPersonCamera();

		/*
			Directions: UP, DOWN, LEFT, RIGHT
		*/
		void ProcessRotation(CameraMovement direction, DeltaTime dt);
		void ProcessMouseMovement(float xMousePos, float yMousePos);
		void ProcessMouseMovementShift(float xoffset, float yoffset);
		void ProcessMouseScroll(float yoffset);
		void UpdateCameraAngles(DeltaTime dt);
		glm::mat4 GetLookatMat();
	};

}