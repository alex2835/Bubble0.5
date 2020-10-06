#pragma once

#include "glm/glm.hpp"
#include <string>


namespace Bubble
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::mat4 transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	
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