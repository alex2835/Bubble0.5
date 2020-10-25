#pragma once

#include "camera.h"


namespace Bubble
{
	struct ThirdPersonCamera : public Camera 
	{
		void ProcessMovement(CameraMovement direction, DeltaTime dt);
		void ProcessMouseMovement(float xMousePos, float yMousePos);
		void ProcessMouseMovementShift(float xoffset, float yoffset);
		void ProcessMouseScroll(float yoffset);
	};

}