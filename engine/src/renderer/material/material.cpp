
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


	DefaultMaterial::DefaultMaterial(std::vector<Texture2D>&& diffuse_maps,
									 std::vector<Texture2D>&& specular_maps,
									 std::vector<Texture2D>&& normal_maps,
									 int shininess)
		: DiffuseMaps(std::move(diffuse_maps)),
		  SpecularMaps(std::move(specular_maps)),
		  NormalMaps(std::move(normal_maps)),
		  Shininess(shininess)
	{}

	void DefaultMaterial::Set(const Ref<Shader>& shader) const
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