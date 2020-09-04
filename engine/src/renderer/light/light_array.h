#pragma once

#include "renderer_base.h"
#include "shader/shader.h"
#include "light.h"

#include <vector>


namespace Bubble
{
	class LightArray
	{
		std::vector<Light> m_Lights;

	public:
		// It must be a child of shader class
		template <typename ShaderType>
		void ApplyLights(const Ref<ShaderType>& shader);

		Light& operator[] (int index) { return m_Lights[index]; }
		void push_back(const Light& lihgt) { m_Lights.push_back(lihgt); }
		void erise(int index) { m_Lights.erase(begin() + index); }
		int size() { return m_Lights.size(); }

		std::vector<Light>::iterator begin() { return m_Lights.begin(); };
		std::vector<Light>::iterator end() { return m_Lights.end(); };
	};


	template <typename ShaderType>
	void Bubble::LightArray::ApplyLights(const Ref<ShaderType>& shader)
	{
		shader->Bind();
		char light_id[64];
		char buffer[64];
		for (int i = 0; i < m_Lights.size(); i++)
		{
			const Light& light = m_Lights[i];
			sprintf_s(light_id, "lights[%d]", i);
			
			sprintf_s(buffer, "%s.type", light_id);
			shader->SetUni1i(buffer, (int)light.Type);
			sprintf_s(buffer, "%s.direction", light_id);
			shader->SetUni3f(light_id, light.Direction);
			sprintf_s(buffer, "%s.position", light_id);
			shader->SetUni3f(light_id, light.Position);
			
			sprintf_s(buffer, "%s.constant", light_id);
			shader->SetUni1f(light_id, light.Constant);
			sprintf_s(buffer, "%s.linear", light_id);
			shader->SetUni1f(light_id, light.Linear);
			sprintf_s(buffer, "%s.quadratic", light_id);
			shader->SetUni1f(light_id, light.Quadratic);
		
			sprintf_s(buffer, "%s.cutOff", light_id);
			shader->SetUni1f(light_id, light.CutOff);
			sprintf_s(buffer, "%s.outerCutOff", light_id);
			shader->SetUni1f(light_id, light.OuterCutOff);
		
			sprintf_s(buffer, "%s.color", light_id);
			shader->SetUni3f(light_id, light.Color);
			sprintf_s(buffer, "%s.brightness", light_id);
			shader->SetUni3f(light_id, light.Brightness);
		}
		shader->SetUni1i("nLights", m_Lights.size());
	}

}