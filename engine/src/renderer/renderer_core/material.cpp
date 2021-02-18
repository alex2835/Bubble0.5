
#include "material.h"


namespace Bubble
{
	BasicMaterial::BasicMaterial(const glm::vec3& ambient,
							     const glm::vec3& diffuse,
							     const glm::vec3& specular,
							     int shininess)
		: mAmbient(ambient),
		  mDiffuse(diffuse),
		  mSpecular(specular),
		  mShininess(shininess)
	{}

	void BasicMaterial::Set(const Ref<Shader>& shader)
	{

	}


	DefaultMaterial::DefaultMaterial(const Ref<Texture2D>& diffuse_map,
									 const Ref<Texture2D>& specular_map,
									 const Ref<Texture2D>& normal_map,
									 int shininess)
		: mDiffuseMap(diffuse_map),
		  mSpecularMap(specular_map),
		  mNormalMap(normal_map),
		  mShininess(shininess)
	{
	}

	void DefaultMaterial::Set(const Ref<Shader>& shader) const
	{
		shader->SetUni1i("material.diffuse", 0);
		mDiffuseMap->Bind(0);

		shader->SetUni1i("material.specular", 1);
		mSpecularMap->Bind(1);

		if (mNormalMap)
		{
			shader->SetUni1i("material.normal", 2);
			mNormalMap->Bind(2);
		}

        shader->SetUni1i("u_NormalMapping", (bool)mNormalMap);
		shader->SetUni1i("material.shininess", mShininess);
	}


	ExtendedMaterial::ExtendedMaterial(std::vector<Ref<Texture2D>>&& diffuse_maps,
									   std::vector<Ref<Texture2D>>&& specular_maps,
									   std::vector<Ref<Texture2D>>&& normal_maps,
									   int shininess)
		: mDiffuseMaps(std::move(diffuse_maps)),
		  mSpecularMaps(std::move(specular_maps)),
		  mNormalMaps(std::move(normal_maps)),
		  mShininess(shininess)
	{}

	void ExtendedMaterial::Set(const Ref<Shader>& shader) const
	{
		int slot = 0;
		for (int i = 0; i < mDiffuseMaps.size(); i++)
		{
			shader->SetUni1i("material.diffuse" + std::to_string(i), slot);
			mDiffuseMaps[i]->Bind(slot++);
		}

		for (int i = 0; i < mSpecularMaps.size(); i++)
		{
			shader->SetUni1i("material.specular" + std::to_string(i), slot);
			mSpecularMaps[i]->Bind(slot++);
		}

		for (int i = 0; i < mNormalMaps.size(); i++)
		{
			shader->SetUni1i("material.normal" + std::to_string(i), slot);
			mNormalMaps[i]->Bind(slot++);
		}

		shader->SetUni1i("material.shininess", mShininess);
		shader->SetUni1i("u_NormalMapping", mNormalMaps.size());
	}

}