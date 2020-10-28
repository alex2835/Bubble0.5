#pragma once

#include "renderer_base.h"

#include "glm/glm.hpp"

#include <utility>
#include <algorithm>


namespace Bubble
{
	enum class LightType { DirLight, PointLight, SpotLight };

	struct Light
	{
		LightType Type;
		float Brightness = 1.0f;
		float Distance = 0.5f;
		glm::vec3 Color = glm::vec3(1.0f);

		// Directional
		glm::vec3 Direction = glm::vec3();
		glm::vec3 Position = glm::vec3();

		// Point
		float Constant = 1.0f;
		float Linear = 0.0f;
		float Quadratic = 0.0f;

		// Spot
		float CutOff = 0.0f;
		float OuterCutOff = 0.0f;

		void SetDistance(float distance);
		void SetDistance();

		static Light CreateDirLight(const glm::vec3& direction = glm::vec3(-1.0f), const glm::vec3& color = glm::vec3(1.0f));
		
		// distance between 0 and 1.0f (where 1.0f is 3250m)
		static Light CreatePointLight(const glm::vec3& position = glm::vec3(), float distance = 0.5f, const glm::vec3& color = glm::vec3(1.0f));
		
		// distance between 0 and 1.0f (where 1.0f is 3250m)
		// cutoff and outer_cutoff in degrees
		static Light CreateSpotLight(const glm::vec3& position = glm::vec3(),
									 const glm::vec3& direction = glm::vec3(1.0f, 0.0f, 0.0f),
									 float distance = 0.5f,
									 float cutoff = 12.5f,
									 float outer_cutoff = 17.5f,
									 const glm::vec3& color = glm::vec3(1.0f));

		template <typename ShaderType>
		static void ApplyLight(const Light& light, const Ref<ShaderType>& shader, int i)
		{
			shader->Bind();
			char light_id[64];
			char buffer[64];
			
			sprintf(light_id, "lights[%d]", i);

			sprintf(buffer, "%s.type", light_id);
			shader->SetUni1i(buffer, (int)light.Type);
			sprintf(buffer, "%s.direction", light_id);
			shader->SetUni3f(buffer, light.Direction);
			sprintf(buffer, "%s.position", light_id);
			shader->SetUni3f(buffer, light.Position);

			sprintf(buffer, "%s.constant", light_id);
			shader->SetUni1f(buffer, light.Constant);
			sprintf(buffer, "%s.linear", light_id);
			shader->SetUni1f(buffer, light.Linear);
			sprintf(buffer, "%s.quadratic", light_id);
			shader->SetUni1f(buffer, light.Quadratic);

			sprintf(buffer, "%s.cutOff", light_id);
			shader->SetUni1f(buffer, cosf(glm::radians(light.CutOff)));
			sprintf(buffer, "%s.outerCutOff", light_id);
			shader->SetUni1f(buffer, cosf(glm::radians(light.OuterCutOff)));

			sprintf(buffer, "%s.color", light_id);
			shader->SetUni3f(buffer, light.Color);

			sprintf(buffer, "%s.brightness", light_id);
			shader->SetUni1f(buffer, light.Brightness);
			
			//shader->SetUni1i("nLights", mLights.size());
		}
	};
}