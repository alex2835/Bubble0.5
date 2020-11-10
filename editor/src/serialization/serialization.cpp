
#include "serialization.h"


namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene, UI* ui)
	{
		nlohmann::json json;

		// Save scene
		json["Scene"] = SerializeScene(scene->Registry);

		// Save skyboxes
		for (const auto& [path, skybox] : SkyboxLoader::LoadedSkyboxes)
		{
			json["Skybox"]["Paths"].push_back(path);
		}
		json["Skybox"]["First"] = SkyboxLoader::LoadedSkyboxes[ui->mScenePanel.nSelectedFirts].first;
		json["Skybox"]["Second"] = SkyboxLoader::LoadedSkyboxes[ui->mScenePanel.nSelectedSecond].first;
		json["Skybox"]["Brightness"] = Renderer::SkyboxBrightness;
		json["Skybox"]["BlendFactor"] = Renderer::SkyboxBlendFactor;
		json["Skybox"]["Rotation"] = Renderer::SkyboxRotation;

		// Save models
		// ...

		// Save UI state
		json["Skybox"]["FirstID"] = ui->mScenePanel.nSelectedFirts;
		json["Skybox"]["SecondID"] = ui->mScenePanel.nSelectedSecond;

		// Dump
		std::ofstream fstream(path);
		fstream << json.dump(1);
		fstream.close();
	}

	void OpenProject(const std::string& path, Scene* scene, UI* ui)
	{
		std::ifstream ifstream(path);
		nlohmann::json json;

		if (!ifstream.is_open())
			throw std::runtime_error("Path to project not valid : " + path);
		
		ifstream >> json;
		ifstream.close();

		// Load scene
		DeserializeScene(scene->Registry, json["Scene"]);

		// Load skyboxes
		for (const auto& path : json["Skybox"]["Paths"])
		{
			SkyboxLoader::Load(path);
		}
		Renderer::SkyboxFirst = SkyboxLoader::Load(json["Skybox"]["First"]);
		Renderer::SkyboxSecond = SkyboxLoader::Load(json["Skybox"]["Second"]);
		Renderer::SkyboxBrightness = json["Skybox"]["Brightness"];
		Renderer::SkyboxBlendFactor = json["Skybox"]["BlendFactor"];
		Renderer::SkyboxRotation = json["Skybox"]["Rotation"];

		// Load models
		// ...

		// Load UI state
		ui->mScenePanel.nSelectedFirts = json["Skybox"]["FirstID"];
		ui->mScenePanel.nSelectedSecond = json["Skybox"]["SecondID"];
	}

}

