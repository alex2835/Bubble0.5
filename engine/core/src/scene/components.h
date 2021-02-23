#pragma once

#include "nlohmann/json.hpp"
#include "glm/glm.hpp"

#include "loader.h"
#include "light.h"

#include <string>
#include <algorithm>

namespace Bubble
{
    inline nlohmann::json to_json(const glm::vec3& vec)
    {
        return nlohmann::json{ vec.r, vec.g, vec.b };
    }
    inline glm::vec3 from_json_vec3(const nlohmann::json& j)
    {
        return glm::vec3(j[0], j[1], j[2]);
    }
    static inline nlohmann::json to_json(const glm::vec4& vec)
    {
        return nlohmann::json{ vec.r, vec.g, vec.b, vec.a };
    }
    static inline glm::vec4 from_json_vec4(const nlohmann::json& j)
    {
        return glm::vec4(j[0], j[1], j[2], j[3]);
    }
    static inline bool json_exists(const nlohmann::json& j, const std::string& key)
    {
        return j.find(key) != j.end();
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

		nlohmann::json Serialize(const Loader& loader) const
		{
			nlohmann::json j;
			j["Tag"] = mTag;
			return j;
		}

		void Deserialize(const nlohmann::json& j, Loader& loader)
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

		nlohmann::json Serialize(const Loader& loader) const
		{
			nlohmann::json j;
			j["Position"] = to_json(mPosition);
			return j;
		}

		void Deserialize(const nlohmann::json& j, Loader& loader)
		{
			mPosition = from_json_vec3(j["Position"]);
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

		nlohmann::json Serialize(const Loader& loader) const
		{
			nlohmann::json j;
			j["Rotation"] = to_json(mRotation);
			return j;
		}

		void Deserialize(const nlohmann::json& j, Loader& loader)
		{
			mRotation = from_json_vec3(j["Rotation"]);
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

		nlohmann::json Serialize(const Loader& loader) const
		{
			nlohmann::json j;
			j["Scale"] = to_json(mScale);
			return j;
		}
		
		void Deserialize(const nlohmann::json& j, Loader& loader)
		{
			mScale = from_json_vec3(j["Scale"]);
		}
	};


	// ================= Transform Component =================
	struct TransformComponent
	{
		glm::mat4 mTransform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::mat4 transform)
			: mTransform(transform)
		{}

		operator glm::mat4& () { return mTransform; }
		operator const glm::mat4& () const { return mTransform; }

		nlohmann::json Serialize(const Loader& loader) const
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

		void Deserialize(const nlohmann::json& j, Loader& loader)
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
		nlohmann::json Serialize(const Loader& loader) const
		{
			nlohmann::json j;
			j["Light"]["Type"]		 = Type;
			j["Light"]["Brightness"] = Brightness;
			j["Light"]["Distance"]   = Distance;

			j["Light"]["Constant"]  = Constant;
			j["Light"]["Linear"]    = Linear;
			j["Light"]["Quadratic"] = Quadratic;

			j["Light"]["CutOff"]	  = CutOff;
			j["Light"]["OuterCutOff"] = OuterCutOff;

			j["Light"]["Position"]  = to_json(Position);
			j["Light"]["Color"]     = to_json(Color);
			j["Light"]["Direction"] = to_json(Direction);
			return j;
		}

		void Deserialize(const nlohmann::json& j, Loader& loader)
		{
			Type	   = j["Light"]["Type"];
			Brightness = j["Light"]["Brightness"];
			Distance   = j["Light"]["Distance"];
			
			Constant  = j["Light"]["Constant"];
			Linear    = j["Light"]["Linear"];
			Quadratic = j["Light"]["Quadratic"];

			CutOff		= j["Light"]["CutOff"];
			OuterCutOff = j["Light"]["OuterCutOff"];

			Position  = from_json_vec3(j["Light"]["Position"]);
			Direction = from_json_vec3(j["Light"]["Direction"]);
			Color     = from_json_vec3(j["Light"]["Color"]);
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

		nlohmann::json Serialize(const Loader& loader) const
		{
			nlohmann::json j;
			auto iterator = std::ranges::find_if(loader.mLoadedModels,
				[&](const auto& path_model) {return path_model.second == *this; });
			
			const std::string& path = iterator->first;
			j["Model"] = path;
			return j;
		}

		void Deserialize(const nlohmann::json& j, Loader& loader)
		{
			*this = loader.LoadModel(j["Model"]);
		}

	};

}