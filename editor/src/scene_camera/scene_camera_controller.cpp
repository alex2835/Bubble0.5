
#include "scene_camera_controller.h"


namespace Bubble
{
	void SceneCameraController::OnUpdate(DeltaTime dt)
	{
		// TODO: continue after Input class
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