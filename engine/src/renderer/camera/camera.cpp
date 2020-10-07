
#include "camera.h"


namespace Bubble
{
   
    // Constructor with vectors
    Camera::Camera(const glm::vec3& position, float yaw, float pitch, float fov, const glm::vec3& up)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Fov = fov;
        UpdateCameraVectors();
    }


    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 Camera::GetLookatMat()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 Camera::GetPprojectionMat(int window_width, int window_height)
    {
        float aspect = (float)window_width / window_height;
        return glm::perspective<float>(Fov, aspect, Near, Far);
    }

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void Camera::UpdateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cosf(Yaw) * cosf(Pitch);
		front.y = sinf(Pitch);
		front.z = sinf(Yaw) * cosf(Pitch);
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}