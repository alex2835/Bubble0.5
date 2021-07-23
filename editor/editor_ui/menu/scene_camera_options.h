#pragma once

#include "imgui.h"
#include "scene_camera.h"

namespace Bubble
{
    inline void SceneCameraOptions(SceneCamera* camera)
    {
        float angles = glm::degrees(camera->Fov);
        ImGui::SliderFloat("FOV", &angles, 5, 90);
        camera->Fov = glm::radians(angles);
        ImGui::SliderFloat("Far plane", &camera->Far, 120.0f, 10000.0f);
        ImGui::SliderFloat("Speed", &camera->DeltaSpeed, 1.0f, 10.0f);
        ImGui::SliderFloat("Boost", &camera->mBoostSpeed, 1.0f, 10.0f);
    }
}