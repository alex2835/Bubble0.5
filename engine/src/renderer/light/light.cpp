
#include "light.h"


namespace Bubble
{
	std::pair<float, float>
		AttenuationLookup[] = {		   // Distance in Meters
				{0.7f	 ,1.8f       } , // 7	
				{0.35f	 ,0.44f	     } , // 13	
				{0.22f	 ,0.20f      } , // 20	
				{0.14f	 ,0.07f	     } , // 32	
				{0.09f	 ,0.032f     } , // 50	
				{0.07f	 ,0.017f     } , // 65	
				{0.045f	 ,0.0075f    } , // 100	
				{0.027f	 ,0.0028f    } , // 160	
				{0.022f	 ,0.0019f    } , // 200	
				{0.014f	 ,0.0007f    } , // 325	
				{0.007f	 ,0.0002f    } , // 600	
				{0.0014f ,0.000007f  }, // 3250
				//{0.0007f, 0.00000035f},
				//{0.0003f, 0.00000007f}
	};


	// Take distance between 0 and 1.0f (where 0 = 7m and 1.0f = 3250m)
	static std::pair<float, float> GetAttenuationConstans(float distance)
	{
		float index = distance * 11.0f; // 11 is array size
		float hight_coef = index - floor(index);
		float lower_coef = 1.0f - (index - floor(index));

		int nIndex = index;
		auto first = AttenuationLookup[std::min(nIndex, 11)];
		auto second = AttenuationLookup[std::min((nIndex + 1), 11)];

		// linear interpolation
		return { first.first * lower_coef + second.first * hight_coef,
				first.second * lower_coef + second.second * hight_coef };
	}

	void Light::SetDistance(float distance)
	{
		auto [linear, quadratic] = GetAttenuationConstans(distance);
		__Distance = distance;
		Linear = linear;
		Quadratic = quadratic;
	}

	void Light::Update()
	{
		auto [linear, quadratic] = GetAttenuationConstans(__Distance);
		Linear = linear;
		Quadratic = quadratic;
		CutOff = cosf(glm::radians(__CutOff));
		OuterCutOff = cosf(glm::radians(__OuterCutOff));
	}

	Light Light::CreateDirLight(const glm::vec3& direction, const glm::vec3& color)
	{
		Light light;
		light.Type = LightType::DirLight;
		light.Direction = glm::normalize(direction);
		light.Color = color;
		return light;
	}

	Light Light::CreatePointLight(const glm::vec3& position, float distance, const glm::vec3& color)
	{
		Light light;
		light.Position = position;
		light.Type = LightType::PointLight;
		light.__Distance = distance;
		light.Color = color;
		light.Update();
		return light;
	}

	Light Light::CreateSpotLight(const glm::vec3& position,
								 const glm::vec3& direction,
								 float distance, 
								 float cutoff,
								 float outer_cutoff,
								 const glm::vec3& color)
	{
		Light light;
		light.Type = LightType::SpotLight;
		light.Position = position;
		light.Direction = glm::normalize(direction);
		light.__Distance = distance;
		light.__CutOff = cutoff;
		light.__OuterCutOff = outer_cutoff;
		light.Color = color;
		light.Update();
		return light;
	}

}