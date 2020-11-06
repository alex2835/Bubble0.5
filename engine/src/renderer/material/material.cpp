
#include "material.h"


namespace Bubble
{
	BasicMaterial::BasicMaterial(const glm::vec3& ambient,
							     const glm::vec3& diffuse,
							     const glm::vec3& specular,
							     int shininess)
		: Ambient(ambient),
		  Diffuse(diffuse),
		  Specular(specular),
		  Shininess(shininess)
	{}

	void BasicMaterial::Set(const Ref<Shader>& shader)
	{

	}


	DefaultMaterial::DefaultMaterial(Texture2D&& diffuse_map,
									 Texture2D&& specular_map,
									 Texture2D&& normal_map,
									 int shininess)
		: Diffuse(std::move(diffuse_map)),
		  Specular(std::move(specular_map)),
		  Normal(std::move(normal_map)),
		  Shininess(shininess)
	{
	}

	void DefaultMaterial::Set(const Ref<Shader>& shader) const
	{
		shader->SetUni1i("material.diffuse0", 0);
		Diffuse.Bind(0);

		shader->SetUni1i("material.specular0", 1);
		Specular.Bind(1);

		shader->SetUni1i("material.normal0", 2);
		Normal.Bind(2);

		shader->SetUni1i("material.shininess", Shininess);
	}



	ExtendedMaterial::ExtendedMaterial(std::vector<Texture2D>&& diffuse_maps,
									   std::vector<Texture2D>&& specular_maps,
									   std::vector<Texture2D>&& normal_maps,
									   int shininess)
		: DiffuseMaps(std::move(diffuse_maps)),
		  SpecularMaps(std::move(specular_maps)),
		  NormalMaps(std::move(normal_maps)),
		  Shininess(shininess)
	{}

	void ExtendedMaterial::Set(const Ref<Shader>& shader) const
	{
		int slot = 0;
		for (int i = 0; i < DiffuseMaps.size(); i++)
		{
			shader->SetUni1i("material.diffuse" + std::to_string(i), slot);
			DiffuseMaps[i].Bind(slot++);
		}

		for (int i = 0; i < SpecularMaps.size(); i++)
		{
			shader->SetUni1i("material.specular" + std::to_string(i), slot);
			SpecularMaps[i].Bind(slot++);
		}

		for (int i = 0; i < NormalMaps.size(); i++)
		{
			shader->SetUni1i("material.normal" + std::to_string(i), slot);
			NormalMaps[i].Bind(slot++);
		}

		shader->SetUni1i("material.shininess", Shininess);
	}

}