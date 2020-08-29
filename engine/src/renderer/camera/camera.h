#pragma once

#include "delta_time/delta_time.h"

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
    const static float MAX_SPEED = 20.0f;
    const static float DELTA_SPEED = 1.0f;

    const static float SENSITIVTY = 0.25f;
    const static float FOV = PI / 4;
    
    class Camera
    {
    public:
        // Camera Attributes
        glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        // Euler Angles
        float m_Yaw = -PI / 2.0f;
        float m_Pitch = 0;

        // Camera options
        float m_MaxSpeed = MAX_SPEED;
        float m_SpeedX = 0;
        float m_SpeedY = 0;
        float m_DeltaSpeed = DELTA_SPEED;
        float m_MouseSensitivity = SENSITIVTY;
        float m_Fov = FOV;
        float m_DeltaFov = 0.05f;

        float m_LastMouseX = 0.5f;
        float m_LastMouseY = 0.5f;

        
        // Constructor with vectors
        Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
               float yaw = YAW,
               float pitch = PITCH,
               const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)
        );

        // Constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 GetLookatMat();
        glm::mat4 GetPprojectionMat(int window_width, int window_height, float near = 0.1f, float far = 120.0f);
        
        void ProcessKeyboard(CameraMovement direction, DeltaTime dt);
        
        void ProcessMouseMovement(float xMousePos, float yMousePos);
        void ProcessMouseMovementShift(float xoffset, float yoffset);
        void ProcessMouseScroll(float yoffset);
      
        void UpdateCameraVectors();
    };
}