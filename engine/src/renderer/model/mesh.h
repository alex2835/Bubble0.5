#pragma once

#include "buffer/buffer.h"
#include "texture/texture.h"
#include "vertex_array/vertex_array.h"

#include "glm/glm.hpp"
#include <vector>


namespace Bubble
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	enum class TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };

	struct MeshTexture : public Texture2D
	{
		TextureType type;

		MeshTexture() = default;
		MeshTexture(const std::string& path);
	};

	struct Mesh
	{
		VertexArray VertexArray;
		Ref<std::vector<Vertex>> Vertices;
		Ref<std::vector<uint32_t>> Indices;
		Ref<std::vector<MeshTexture>> Textures;

		Mesh(const Ref<std::vector<Vertex>>& vertices,
			 const Ref<std::vector<uint32_t>>& indices,
			 const Ref<std::vector<MeshTexture>>& textures);

		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;

		Mesh(Mesh&&) = default;
		Mesh& operator= (Mesh&&) = default;

		const std::vector<MeshTexture>& GetTextures() const { return *Textures.get(); }
	};

}