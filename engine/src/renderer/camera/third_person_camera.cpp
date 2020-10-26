
#include "third_person_camera.h"


namespace Bubble
{

	ThirdPersonCamera::ThirdPersonCamera()
		: Center(glm::vec3(0, 5, 0))
	{}


	void ThirdPersonCamera::ProcessRotation(CameraMovement direction, DeltaTime dt)
	{
		float max_speed = MaxSpeed * DeltaSpeed;

		// Speed x
		if (direction == CameraMovement::LEFT)
		{
			if (SpeedX < 0)
				SpeedX = 0;
			SpeedX = SpeedX < max_speed ? SpeedX + DeltaSpeed : max_speed;
			IsRotatingX = true;
		}
		else if (direction == CameraMovement::RIGHT)
		{
			if (SpeedX > 0)
				SpeedX = 0;
			SpeedX = SpeedX > -max_speed ? SpeedX - DeltaSpeed : -max_speed;
			IsRotatingX = true;
		}

		// Speed y
		if (direction == CameraMovement::UP)
		{
			if (SpeedY < 0)
				SpeedY = 0;
			SpeedY = SpeedY < max_speed ? SpeedY + DeltaSpeed : max_speed;
			IsRotatingY = true;
		}
		else if (direction == CameraMovement::DOWN)
		{
			if (SpeedY > 0)
				SpeedY = 0;
			SpeedY = SpeedY > -max_speed ? SpeedY - DeltaSpeed : -max_speed;
			IsRotatingY = true;
		}

		// Speed z
		// ...

		// Clamp
		if (fabs(SpeedX) > max_speed)
			SpeedX = sgn(SpeedX) * max_speed;

		if (fabs(SpeedY) > max_speed)
			SpeedY = sgn(SpeedY) * max_speed;
	}


	void ThirdPersonCamera::ProcessMouseMovement(float MousePosX, float MousePosY)
	{
		float xoffset = (LastMouseX - MousePosX) * MouseSensitivity;
		float yoffset = (LastMouseY - MousePosY) * MouseSensitivity;

		LastMouseX = MousePosX;
		LastMouseY = MousePosY;

		Yaw -= xoffset;
		Pitch -= yoffset;

		if (Pitch > PI / 2.0f - 0.1f)
			Pitch = PI / 2.0f - 0.1f;
		
		if (Pitch < -PI / 2.0f + 0.1f)
			Pitch = -PI / 2.0f + 0.1f;
	}


	void ThirdPersonCamera::ProcessMouseMovementShift(float xoffset, float yoffset)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (Pitch > PI / 2.0f - 0.1f)
			Pitch = PI / 2.0f - 0.1f;

		if (Pitch < -PI / 2.0f + 0.1f)
			Pitch = -PI / 2.0f + 0.1f;
	}


	void ThirdPersonCamera::ProcessMouseScroll(float yoffset)
	{
		if (Fov >= 0.1f && Fov <= PI / 2.0f)
			Fov -= yoffset * DeltaFov;

		if (Fov < 0.1f)
			Fov = 0.1f;

		if (Fov > PI / 2.0f)
			Fov = PI / 2.0f;
	}


	void ThirdPersonCamera::UpdateCameraAngles(DeltaTime dt)
	{
		// Inertia
		if (!IsRotatingX)
			SpeedX = fabs(SpeedX) < 0.01f ? SpeedX = 0 : SpeedX - sgn(SpeedX) * DeltaSpeed;

		if (!IsRotatingY)
			SpeedY = fabs(SpeedY) < 0.01f ? SpeedY = 0 : SpeedY - sgn(SpeedY) * DeltaSpeed;

		IsRotatingX = false;
		IsRotatingY = false;

		Yaw += SpeedX * dt.GetSeconds();
		Pitch += SpeedY * dt.GetSeconds();

		// Rotating
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, Yaw, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, Pitch, glm::vec3(1, 0, 0));
		transform = glm::translate(transform, Center);
		Position = transform * glm::vec4(0, 0, Radius, 0);

		// Basis
		Front = glm::normalize(Center - Position);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}


	glm::mat4 ThirdPersonCamera::GetLookatMat()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
}