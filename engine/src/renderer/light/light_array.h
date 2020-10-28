#pragma once

#include "renderer_base.h"
#include "shader/shader.h"
#include "light.h"

#include <vector>


namespace Bubble
{
	class LightArray
	{
		std::vector<Light> mLights;

	public:
		// It must be a child of shader class
		template <typename ShaderType>
		void ApplyLights(const Ref<ShaderType>& shader);

		Light& operator[] (int index) { return mLights[index]; }
		void push_back(const Light& lihgt) { mLights.push_back(lihgt); }
		void erise(int index) { mLights.erase(begin() + index); }
		int size() { return mLights.size(); }

		std::vector<Light>::iterator begin() { return mLights.begin(); };
		std::vector<Light>::iterator end() { return mLights.end(); };
	};


	template <typename ShaderType>
	void Bubble::LightArray::ApplyLights(const Ref<ShaderType>& shader)
	{
		shader->Bind();
		char light_id[64];
		char buffer[64];
		for (int i = 0; i < mLights.size(); i++)
		{
			const Light& light = mLights[i];
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
		}
		shader->SetUni1i("nLights", mLights.size());
	}


}