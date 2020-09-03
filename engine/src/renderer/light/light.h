#pragma once

#include "glm/glm.hpp"
#include <utility>


namespace Bubble
{
	enum class LightType { DirLight, PointLight, SpotLight };

	struct Light
	{
		LightType Type;
		float Brightness = 1.0f;
		float Distance = 0.1f;
		glm::vec3 Color = glm::vec3{ 1.0f };

		// Directional
		glm::vec3 Direction;
		glm::vec3 Position;

		// Point
		float Constant = 1.0f;
		float Linear;
		float Quadratic;

		// Spot
		float CutOff;
		float OuterCutOff;

		void SetDistance(float distance);

		static Light CreateDirLight(const glm::vec3& direction, const glm::vec3& color = glm::vec3(1.0f));
		
		// distance between 0 and 1.0f (where 1.0f is 3500m)
		static Light CreatePointLight(const glm::vec3& position, float distance = 0.1f, const glm::vec3& color = glm::vec3(1.0f));
		
		// distance between 0 and 1.0f (where 1.0f is 3500m)
		// cutoff and outer_cutoff in degrees
		static Light CreateSpotLight(const glm::vec3& position, 
									 const glm::vec3& direction,
									 float distance = 0.1f,
									 float cutoff = 12.5f,
									 float outer_cutoff = 17.5f,
									 const glm::vec3& color = glm::vec3(1.0f));
	};
}