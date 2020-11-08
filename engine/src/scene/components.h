#pragma once

#include "nlohmann/json.hpp"
#include "glm/glm.hpp"

#include "Light/Light.h"
#include "model/model_loader.h"

#include <string>
#include <algorithm>


namespace Bubble
{
	inline nlohmann::json to_json(const glm::vec3& value)
	{
		return { value.r, value.g, value.b };
	}

	inline glm::vec3 from_json(const nlohmann::json& value)
	{
		return glm::vec3(value[0], value[1], value[2]);
	}


	// ================= TagComponent =================
	struct TagComponent
	{
		std::string mTag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: mTag(tag) {}

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			j["Tag"] = mTag;
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			mTag = j["Tag"];
		}
	};


	// ================= PositionComponent =================
	struct PositionComponent
	{
		glm::vec3 mPosition;

		PositionComponent() = default;
		PositionComponent(const glm::vec3& mPosition)
			: mPosition(mPosition)
		{}

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			j["Position"] = to_json(mPosition);
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			mPosition = from_json(j["Position"]);
		}

	};


	// ================= RotationComponent =================
	struct RotationComponent
	{
		glm::vec3 mRotation;

		RotationComponent() = default;
		RotationComponent(const glm::vec3& rotation)
			: mRotation(rotation)
		{}

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			j["Rotation"] = to_json(mRotation);
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			mRotation = from_json(j["Rotation"]);
		}

	};


	// ================= ScaleComponent =================
	struct ScaleComponent 
	{ 
		glm::vec3 mScale = glm::vec3( 1.0f );
		
		ScaleComponent() = default;
		ScaleComponent(const glm::vec3 & scale)
			: mScale(scale)
		{}

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			j["Scale"] = to_json(mScale);
			return j;
		}
		
		void Deserialize(const nlohmann::json& j)
		{
			mScale = from_json(j["Scale"]);
		}
	};


	// ================= TransformComponent =================
	struct TransformComponent
	{
		glm::mat4 mTransform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::mat4 transform)
			: mTransform(transform) {}

		operator glm::mat4& () { return mTransform; }
		operator const glm::mat4& () const { return mTransform; }

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			std::vector<float> temp;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					temp.push_back(mTransform[i][j]);
				}
			}
			j["Transform"] = temp;
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			std::vector<float> temp = j["Transform"];
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					mTransform[i][j] = temp[i * 4 + j];
				}
			}

		}

	};


	// ================= LightComponent =================
	struct LightComponent
	{
		Light mLight;

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			j["Light"]["Type"] = mLight.Type;
			j["Light"]["Brightness"] = mLight.Brightness;
			j["Light"]["Distance"] = mLight.__Distance;
			j["Light"]["Color"] = to_json(mLight.Color);

			j["Light"]["Direction"] = to_json(mLight.Direction);
			j["Light"]["Position"] = to_json(mLight.Position);

			j["Light"]["Constant"] = mLight.Constant;
			j["Light"]["Linear"] = mLight.Linear;
			j["Light"]["Quadratic"] = mLight.Quadratic;

			j["Light"]["CutOff"] = mLight.__CutOff;
			j["Light"]["OuterCutOff"] = mLight.__OuterCutOff;

			return j;
		}


		void Deserialize(const nlohmann::json& j)
		{
			mLight.Type= j["Light"]["Type"];
			mLight.Brightness = j["Light"]["Brightness"];
			mLight.__Distance = j["Light"]["Distance"];
			mLight.Color = from_json(j["Light"]["Color"]);

			mLight.Direction = from_json(j["Light"]["Direction"]);
			mLight.Position = from_json(j["Light"]["Position"]);

			mLight.Constant = j["Light"]["Constant"];
			mLight.Linear= j["Light"]["Linear"];
			mLight.Quadratic = j["Light"]["Quadratic"];

			mLight.__CutOff = j["Light"]["CutOff"];
			mLight.__OuterCutOff = j["Light"]["OuterCutOff"];
		}

	};

	// ================= ModelComponent =================
	struct ModelComponent : Ref<Model>
	{
		//Ref<Model> mModel;

		ModelComponent() = default;
		ModelComponent(const Ref<Model>& model)
			: Ref<Model>(model)
		{}
		
		operator Ref<Model>& () { return *this; }
		operator const Ref<Model>& () const { return *this; }

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			auto iterator = *(std::find_if(
				ModelLoader::LoadedModels.begin(), ModelLoader::LoadedModels.end(),
				[&](const std::pair<std::string, Ref<Model>>& path_model) 
				{
					return path_model.second == *this;
				}
			));

			std::string path = iterator.first;
			j["Model"] = path;
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			*this = ModelLoader::StaticModel(j["Model"]);
		}

	};


	// =================
	//class ScriptableEntity;
	//
	//class NativeScriptComponent
	//{
	//public:
	//	ScriptableEntity* Instance = nullptr;
	//
	//	ScriptableEntity* (*InstantiateScript)();
	//	void (*DestroyInstanceScript)(NativeScriptComponent*);
	//
	//	template <typename T>
	//	void Bind()
	//	{
	//		InstantiateScript = []() { return (ScriptableEntity*)new T(); };
	//		DestroyInstanceScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
	//	}
	//
	//
	//};

}