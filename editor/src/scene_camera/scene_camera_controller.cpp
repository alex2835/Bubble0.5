
#include "scene_camera_controller.h"


namespace Bubble
{
	// Process scene camera movement
	void SceneCameraController::OnUpdate(DeltaTime dt)
	{
		if (Input::IsMouseButtonPressed(SDL_BUTTON_LEFT))
		{
			// Catch cursor
			SDL_CaptureMouse(SDL_TRUE);

			// speed x
			if (Input::IsKeyPressed(SDLK_w))
			{
				m_Camera.m_SpeedX = m_Camera.m_SpeedX < m_Camera.m_MaxSpeed ? m_Camera.m_SpeedX + m_Camera.m_DeltaSpeed : m_Camera.m_MaxSpeed;
			}
			else if (Input::IsKeyPressed(SDLK_s))
			{
				m_Camera.m_SpeedX = m_Camera.m_SpeedX > -m_Camera.m_MaxSpeed ? m_Camera.m_SpeedX - m_Camera.m_DeltaSpeed : -m_Camera.m_MaxSpeed;
			}
			else {
				m_Camera.m_SpeedX = fabs(m_Camera.m_SpeedX) < 0.01f ? m_Camera.m_SpeedX = 0 : m_Camera.m_SpeedX - sgn(m_Camera.m_SpeedX) * m_Camera.m_DeltaSpeed;
			}

			// speed y
			if (Input::IsKeyPressed(SDLK_d))
			{
				m_Camera.m_SpeedY = m_Camera.m_SpeedY < m_Camera.m_MaxSpeed ? m_Camera.m_SpeedY + m_Camera.m_DeltaSpeed : m_Camera.m_MaxSpeed;
			}
			else if (Input::IsKeyPressed(SDLK_a))
			{
				m_Camera.m_SpeedY = m_Camera.m_SpeedY > -m_Camera.m_MaxSpeed ? m_Camera.m_SpeedY - m_Camera.m_DeltaSpeed : -m_Camera.m_MaxSpeed;
			}
			else {
				m_Camera.m_SpeedY = fabs(m_Camera.m_SpeedY) < 0.01f ? m_Camera.m_SpeedY = 0 : m_Camera.m_SpeedY - sgn(m_Camera.m_SpeedY) * m_Camera.m_DeltaSpeed;
			}

			// clamp
			if (fabs(m_Camera.m_SpeedX) > m_Camera.m_MaxSpeed)
			{
				m_Camera.m_SpeedX = sgn(m_Camera.m_SpeedX) * m_Camera.m_MaxSpeed;
			}
			
			if (fabs(m_Camera.m_SpeedY) > m_Camera.m_MaxSpeed)
			{
				m_Camera.m_SpeedY = sgn(m_Camera.m_SpeedY) * m_Camera.m_MaxSpeed;
			}

			// move
			m_Camera.m_Position += m_Camera.m_Front * m_Camera.m_SpeedX * dt.GetSeconds();
			m_Camera.m_Position += m_Camera.m_Right * m_Camera.m_SpeedY * dt.GetSeconds();

			m_Camera.ProcessMouseMovementShift(Input::fGetMouseRelX(), Input::fGetMouseRelY());
			m_Camera.ProcessMouseScroll(Input::GetMouseWheelOffset());

			m_Camera.UpdateCameraVectors();
		}
		else {
			// Release cursor
			SDL_CaptureMouse(SDL_FALSE);
		}
	}

	glm::mat4 SceneCameraController::GetLookatMat()
	{
		return m_Camera.GetLookatMat();
	}

	glm::mat4 SceneCameraController::GetPprojectionMat(int window_width, int window_height, float near, float far)
	{
		return m_Camera.GetPprojectionMat(window_width, window_height, near, far);
	}

}