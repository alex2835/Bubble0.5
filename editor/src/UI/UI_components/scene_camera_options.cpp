
#include "scene_camera_options.h"


namespace Bubble
{
	void SceneCameraOptions(SceneCamera* camera)
	{
		float angles = glm::degrees(camera->Fov);
		ImGui::SliderFloat("FOV", &angles, 5, 90);
		camera->Fov = glm::radians(angles);
		ImGui::SliderFloat("Far plane", &camera->Far, 120.0f, 10000.0f);
		ImGui::SliderFloat("Speed", &camera->DeltaSpeed, 1.0f, 10.0f);
		ImGui::SliderFloat("Boost", &camera->BoostSpeed, 1.0f, 10.0f);
	}

}