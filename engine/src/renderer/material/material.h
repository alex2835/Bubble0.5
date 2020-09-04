#pragma once

#include "glm/glm.hpp"
#include "texture/texture.h"
#include "shader/shader.h"

namespace Bubble
{
	//enum class TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };
	//static const char* const TextureNameLookup[] = { "material.diffuse", "material.specular", "material.normal", "material.height" };

	struct BasicMaterial
	{
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		int Shininess;

		BasicMaterial(const glm::vec3& ambient,
					  const glm::vec3& diffuse,
					  const glm::vec3& specular,
					  int shininess = 32);

		void Set(const Ref<Shader>& shader);
	};

	struct DefaultMaterial
	{
		std::vector<Texture2D> DiffuseMaps;
		std::vector<Texture2D> SpecularMaps;
		std::vector<Texture2D> NormalMaps;
		int Shininess = 32;

		DefaultMaterial() = default;
		DefaultMaterial(std::vector<Texture2D>&& diffuse_maps,
						std::vector<Texture2D>&& specular_maps,
						std::vector<Texture2D>&& normal_maps,
						int shininess = 32);

		DefaultMaterial(const DefaultMaterial&) = delete;
		DefaultMaterial& operator=(const DefaultMaterial&) = delete;

		DefaultMaterial(DefaultMaterial&&) = default;
		DefaultMaterial& operator=(DefaultMaterial&&) = default;

		void Set(const Ref<Shader>& shader) const;
	};

	// PBR material and so on

}