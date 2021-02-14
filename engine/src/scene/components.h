#pragma once

#include "nlohmann/json.hpp"
#include "glm/glm.hpp"

#include "loader.h"
#include "light.h"

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

	// ================= Tag Component =================
	struct TagComponent
	{
		std::string mTag;

        TagComponent() { mTag.reserve(256); }
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: mTag(tag)
		{
			mTag.reserve(256);
		}

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


	// ================= Position Component =================
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


	// ================= Rotation Component =================
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


	// ================= Transform Component =================
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


	// ================= Light Component =================
	struct LightComponent : Light
	{
		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			j["Light"]["Type"] = Type;
			j["Light"]["Brightness"] = Brightness;
			j["Light"]["Distance"] = Distance;

			j["Light"]["Constant"] = Constant;
			j["Light"]["Linear"] = Linear;
			j["Light"]["Quadratic"] = Quadratic;

			j["Light"]["CutOff"] = CutOff;
			j["Light"]["OuterCutOff"] = OuterCutOff;

			j["Light"]["Position"] = to_json(Position);
			j["Light"]["Color"] = to_json(Color);
			j["Light"]["Direction"] = to_json(Direction);
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			Type= j["Light"]["Type"];
			Brightness = j["Light"]["Brightness"];
			Distance = j["Light"]["Distance"];
			
			Constant = j["Light"]["Constant"];
			Linear = j["Light"]["Linear"];
			Quadratic = j["Light"]["Quadratic"];

			CutOff = j["Light"]["CutOff"];
			OuterCutOff = j["Light"]["OuterCutOff"];

			Position = from_json(j["Light"]["Position"]);
			Direction = from_json(j["Light"]["Direction"]);
			Color = from_json(j["Light"]["Color"]);
		}

	};

	// ================= Model Component =================
	struct ModelComponent : Ref<Model>
	{
		ModelComponent() = default;
		ModelComponent(const Ref<Model>& model)
			: Ref<Model>(model)
		{}
		
		operator Ref<Model>& () { return *this; }
		operator const Ref<Model>& () const { return *this; }

		nlohmann::json Serialize() const
		{
			nlohmann::json j;
			//auto iterator = std::ranges::find_if(*Loader::sLoadedModels,
			//	[&](const std::pair<std::string, Ref<Model>>& path_model) 
			//	{
			//		return path_model.second == *this;
			//	}
			//);
			//
			//const std::string& path = iterator->first;
			//j["Model"] = path;
			return j;
		}

		void Deserialize(const nlohmann::json& j)
		{
			//*this = Loader::LoadModel(j["Model"]);
		}

	};

}