
#include "scene_camera_options.h"


namespace Bubble
{
	void SceneCameraOptions(SceneCameraController* camera)
	{
		float angles = glm::degrees(camera->m_Camera.Fov);
		ImGui::SliderFloat("FOV", &angles, 5, 90);
		camera->m_Camera.Fov = glm::radians(angles);
		ImGui::SliderFloat("Far plane", &camera->m_Camera.Far, 120.0f, 1500.0f);
		ImGui::SliderFloat("Speed", &camera->DeltaSpeed, 1.0f, 10.0f);
		ImGui::SliderFloat("Boost", &camera->BoostSpeed, 1.0f, 10.0f);
	}

}