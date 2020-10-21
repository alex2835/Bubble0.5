
#include "serialization.h"


namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene)
	{
		nlohmann::json json;

		// Save scene
		json["Scene"] = SerializeScene(scene->m_Registry);

		std::ofstream fstream(path);
		fstream << json.dump(1);
		fstream.close();
	}

	void OpenProject(const std::string& path, Scene* scene)
	{
		std::ifstream ifstream(path);
		nlohmann::json json;

		if (!ifstream.is_open())
			throw std::runtime_error("Path to project not valid : " + path);
		
		ifstream >> json;
		ifstream.close();

		// Open scene
		DeserializeScene(scene->m_Registry, json["Scene"]);

	}

}

