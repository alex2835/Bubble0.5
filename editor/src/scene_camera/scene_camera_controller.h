#pragma once

#include "input/input.h"
#include "camera/camera.h"
#include "delta_time/delta_time.h"

#include "SDL2/SDL.h"

namespace Bubble
{
	const static float MAX_SPEED = 20.0f;
	const static float DELTA_SPEED = 1.0f;
	const static float SENSITIVTY = 4.25f;


	struct SceneCameraController
	{
		Camera m_Camera;
		float m_LastMouseX = 0.5f;
		float m_LastMouseY = 0.5f;

	public:
		// Camera options
		float MaxSpeed = MAX_SPEED;
		float DeltaSpeed = DELTA_SPEED;
		float SpeedX = 0;
		float SpeedY = 0;
		float MouseSensitivity = SENSITIVTY;
		float DeltaFov = 0.05f;

	public:
		SceneCameraController(const glm::vec3& position = glm::vec3(0.0f));
		void OnUpdate(DeltaTime dt);

		glm::mat4 GetLookatMat();
		glm::mat4 GetPprojectionMat(int WindowWidth, int WindowHeight, float near_plane = 0.1f, float far_plane = 120.0f);

	private:
		void ProcessKeyboard(CameraMovement direction, DeltaTime dt);
		void ProcessMouseMovement(float xMousePos, float yMousePos);
		void ProcessMouseMovementShift(float xoffset, float yoffset);
		void ProcessMouseScroll(float yoffset);
	};

}