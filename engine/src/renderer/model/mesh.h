#pragma once

#include "buffer/buffer.h"
#include "texture/texture.h"
#include "vertex_array/vertex_array.h"
#include "material/material.h"

#include "glm/glm.hpp"
#include <vector>


namespace Bubble
{
	struct VertexData
	{
		std::vector<glm::vec3> Positions;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec2> TexCoords;
		std::vector<glm::vec3> Tangents;
		std::vector<glm::vec3> Bitangents;
	};


	struct Mesh
	{
		VertexArray mVertexArray;
		DefaultMaterial mMaterial;
		VertexData mVertices;
		std::vector<uint32_t> mIndices;
		
		Mesh() = default;
		Mesh(DefaultMaterial&& Material,
			 VertexData&& vertices,
			 std::vector<uint32_t>&& indices);

		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;

		Mesh(Mesh&&) = default;
		Mesh& operator= (Mesh&&) = default;
	};

}