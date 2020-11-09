#pragma once

#include "renderer_base.h"
#include "shader/shader.h"

#include "glm/glm.hpp"

#include <utility>
#include <algorithm>


namespace Bubble
{
	enum class LightType { DirLight, PointLight, SpotLight };

	/*
		Variables with __ prefix temporary and
		stay at padding places, by this trick
		possible to dump whole array directly
		to shader by one load
	*/


	struct GLSL_Light
	{
		LightType Type;
		float Brightness = 1.0f;

		// Point
		float Constant = 1.0f;
		float Linear = 0.0f;
		float Quadratic = 0.0f;

		// Spot
		float __CutOff = 0.0f;
		float __OuterCutOff = 0.0f;
		float __pad0;

		glm::vec3 Color = glm::vec3(1.0f);
		float __pad1;

		// Directional
		glm::vec3 Direction = glm::vec3();
		float __pad2;

		glm::vec3 Position = glm::vec3();
		float __pad3;
	};


	struct Light : GLSL_Light
	{
		float CutOff = 0.0f;
		float OuterCutOff = 0.0f;
		float Distance = 0.0f;
		
		void SetDistance(float distance);
		void Update();

		static Light CreateDirLight(const glm::vec3& direction = glm::vec3(-1.0f), const glm::vec3& color = glm::vec3(1.0f));
		
		// distance between 0 and 1.0f (where 1.0f is 3250m)
		static Light CreatePointLight(const glm::vec3& position = glm::vec3(), float distance = 0.5f, const glm::vec3& color = glm::vec3(1.0f));
		
		// distance between 0 and 1.0f (where 1.0f is 3250m)
		static Light CreateSpotLight(const glm::vec3& position = glm::vec3(),
									 const glm::vec3& direction = glm::vec3(1.0f, 0.0f, 0.0f),
									 float distance = 0.5f,
									 float cutoff = 12.5f,		// cutoff and outer_cutoff in degrees
									 float outer_cutoff = 17.5f,
									 const glm::vec3& color = glm::vec3(1.0f));
	};
}