#pragma once

#include "time/time.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    NO_DIRECTION
};

namespace Bubble
{
	const float PI = 3.14159265359f;

    template <typename T>
    inline int sgn(T num) { return (num > T(0)) - (num < T(0)); }


    // Default camera values
    const static float YAW = -PI / 2;
    const static float PITCH = 0;
    const static float FOV = PI / 4;
    
    struct Camera
    {
        // Camera Attributes
        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        // Euler Angles
        float Yaw = -PI / 2.0f;
        float Pitch = 0;
		float Fov = FOV;

        Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
               float yaw = YAW,
               float pitch = PITCH,
               float fov = FOV,
               const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 GetLookatMat();
        glm::mat4 GetPprojectionMat(int window_width, int window_height, float near = 0.1f, float far = 120.0f);
        
        void UpdateCameraVectors();
    };
}