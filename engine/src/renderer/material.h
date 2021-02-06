#pragma once

#include "glm/glm.hpp"
#include "texture.h"
#include "shader_loader.h"

namespace Bubble
{
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
		Texture2D Diffuse;
		Texture2D Specular;
		Texture2D Normal;
		int Shininess = 32;

		DefaultMaterial() = default;
		DefaultMaterial(Texture2D&& diffuse_map,
						Texture2D&& specular_map,
						Texture2D&& normal_map,
						int shininess = 32);

		DefaultMaterial(const DefaultMaterial&) = delete;
		DefaultMaterial& operator=(const DefaultMaterial&) = delete;

		DefaultMaterial(DefaultMaterial&&) = default;
		DefaultMaterial& operator=(DefaultMaterial&&) = default;

		void Set(const Ref<Shader>& shader) const;
	};


	struct ExtendedMaterial
	{
		std::vector<Texture2D> DiffuseMaps;
		std::vector<Texture2D> SpecularMaps;
		std::vector<Texture2D> NormalMaps;
		int Shininess = 32;

		ExtendedMaterial() = default;
		ExtendedMaterial(std::vector<Texture2D>&& diffuse_maps,
						 std::vector<Texture2D>&& specular_maps,
						 std::vector<Texture2D>&& normal_maps,
						 int shininess = 32);

		ExtendedMaterial(const ExtendedMaterial&) = delete;
		ExtendedMaterial& operator=(const ExtendedMaterial&) = delete;

		ExtendedMaterial(ExtendedMaterial&&) = default;
		ExtendedMaterial& operator=(ExtendedMaterial&&) = default;

		void Set(const Ref<Shader>& shader) const;
	};


	// PBR material

}