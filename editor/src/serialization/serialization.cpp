
#include "serialization.h"


namespace Bubble
{
	void SaveProject(const std::string& path, const entt::registry& scene)
	{
		nlohmann::json out;

		// Save scene
		out["Scene"] = SerializeScene(scene);


		// Save models

		// Save ...

		std::ofstream fstream(path);
		fstream << out.dump(1);
		fstream.close();
	}

	void OpenProject(const std::string& path, entt::registry& scene)
	{
		std::ifstream ifstream(path);
		nlohmann::json j;

		if (!ifstream.is_open())
			throw std::runtime_error("Path to project not valid : " + path);
		
		ifstream >> j;
		ifstream.close();

		// Open scene
		DeserializeScene(scene, j["Scene"]);


		// Open models


		// Open ...

	}

}

