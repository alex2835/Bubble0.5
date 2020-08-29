#pragma once

#include "glm/glm.hpp"
#include <string>


namespace Bubble
{
	using TransformComponent = glm::mat4;
	using TagComponent = std::string;


	class ScriptableEntity;

	class NativeScriptComponent
	{
	public:
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyInstanceScript)(NativeScriptComponent*);

		template <typename T>
		void Bind()
		{
			InstantiateScript = []() { return (ScriptableEntity*)new T(); };
			DestroyInstanceScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

}