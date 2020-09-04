
#include "scene_camera_controller.h"


namespace Bubble
{
	// Process scene camera movement
	void SceneCameraController::OnUpdate(DeltaTime dt)
	{
		if (Input::IsMouseButtonPressed(SDL_BUTTON_RIGHT))
		{
			// Catch cursor
			SDL_SetRelativeMouseMode(SDL_TRUE);

			// speed x
			if (Input::IsKeyPressed(SDLK_w))
			{
				SpeedX = SpeedX < MaxSpeed ? SpeedX + DeltaSpeed : MaxSpeed;
			}
			else if (Input::IsKeyPressed(SDLK_s))
			{
				SpeedX = SpeedX > -MaxSpeed ? SpeedX - DeltaSpeed : -MaxSpeed;
			}
			else {
				SpeedX = fabs(SpeedX) < 0.01f ? SpeedX = 0 : SpeedX - sgn(SpeedX) * DeltaSpeed;
			}

			// speed y
			if (Input::IsKeyPressed(SDLK_d))
			{
				SpeedY = SpeedY < MaxSpeed ? SpeedY + DeltaSpeed : MaxSpeed;
			}
			else if (Input::IsKeyPressed(SDLK_a))
			{
				SpeedY = SpeedY > -MaxSpeed ? SpeedY - DeltaSpeed : -MaxSpeed;
			}
			else {
				SpeedY = fabs(SpeedY) < 0.01f ? SpeedY = 0 : SpeedY - sgn(SpeedY) * DeltaSpeed;
			}

			// clamp
			if (fabs(SpeedX) > MaxSpeed)
			{
				SpeedX = sgn(SpeedX) * MaxSpeed;
			}
			
			if (fabs(SpeedY) > MaxSpeed)
			{
				SpeedY = sgn(SpeedY) * MaxSpeed;
			}

			// move
			m_Camera.Position += m_Camera.Front * SpeedX * dt.GetSeconds();
			m_Camera.Position -= m_Camera.Right * SpeedY * dt.GetSeconds();

			ProcessMouseMovementShift(-Input::fGetMouseRelX(), -Input::fGetMouseRelY());
			ProcessMouseScroll(-Input::GetMouseWheelOffset());

			m_Camera.UpdateCameraVectors();
		}
		else {
			// Release cursor
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}

	glm::mat4 SceneCameraController::GetLookatMat()
	{
		return m_Camera.GetLookatMat();
	}

	glm::mat4 SceneCameraController::GetPprojectionMat(int window_width, int window_height, float near_plane, float far_plane)
	{
		return m_Camera.GetPprojectionMat(window_width, window_height, near_plane, far_plane);
	}




	void SceneCameraController::ProcessKeyboard(CameraMovement direction, DeltaTime dt)
	{
		if (direction == CameraMovement::FORWARD)
		{
			SpeedX += DeltaSpeed;
		}
		else if (direction == CameraMovement::BACKWARD)
		{
			SpeedX -= DeltaSpeed;
		}
		else {
			SpeedX -= sgn(SpeedX) * DeltaSpeed;
		}

		if (direction == CameraMovement::LEFT)
		{
			SpeedY += DeltaSpeed;
		}
		else if (direction == CameraMovement::RIGHT)
		{
			SpeedY -= DeltaSpeed;
		}
		else {
			SpeedY -= sgn(SpeedY) * DeltaSpeed;
		}

		if (fabs(SpeedX) > MaxSpeed) SpeedX = sgn(SpeedX) * MaxSpeed;
		if (fabs(SpeedY) > MaxSpeed) SpeedY = sgn(SpeedY) * MaxSpeed;

		m_Camera.Position -= m_Camera.Front * SpeedX * dt.GetSeconds();
		m_Camera.Position += m_Camera.Right * SpeedY * dt.GetSeconds();

		m_Camera.UpdateCameraVectors();
	}


	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void SceneCameraController::ProcessMouseMovement(float MousePosX, float MousePosY)
	{
		float xoffset = (m_LastMouseX - MousePosX) * MouseSensitivity;
		float yoffset = (m_LastMouseY - MousePosY) * MouseSensitivity;

		m_LastMouseX = MousePosX;
		m_LastMouseY = MousePosY;

		m_Camera.Yaw -= xoffset;
		m_Camera.Pitch -= yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (m_Camera.Pitch > PI / 2.0f - 0.1f)
			m_Camera.Pitch = PI / 2.0f - 0.1f;

		if (m_Camera.Pitch < -PI / 2.0f + 0.1f)
			m_Camera.Pitch = -PI / 2.0f + 0.1f;

	}

	void SceneCameraController::ProcessMouseMovementShift(float xoffset, float yoffset)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		m_Camera.Yaw += xoffset;
		m_Camera.Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (m_Camera.Pitch > PI / 2.0f - 0.1f)
			m_Camera.Pitch = PI / 2.0f - 0.1f;

		if (m_Camera.Pitch < -PI / 2.0f + 0.1f)
			m_Camera.Pitch = -PI / 2.0f + 0.1f;

	}


	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void SceneCameraController::ProcessMouseScroll(float yoffset)
	{
		if (m_Camera.Fov >= 0.1f && m_Camera.Fov <= PI / 2.0f)
			m_Camera.Fov += yoffset * DeltaFov;

		if (m_Camera.Fov < 0.1f)
			m_Camera.Fov = 0.1f;

		if (m_Camera.Fov > PI / 2.0f)
			m_Camera.Fov = PI / 2.0f;
	}

}