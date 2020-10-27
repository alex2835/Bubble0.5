#pragma once

#include "buffer/buffer.h"
#include "texture/texture.h"
#include "vertex_array/vertex_array.h"
#include "material/material.h"

#include "glm/glm.hpp"
#include <vector>


namespace Bubble
{
	//struct Vertex
	//{
	//	glm::vec3 Position;
	//	glm::vec3 Normal;
	//	glm::vec2 TexCoords;
	//	glm::vec3 Tangent;
	//	glm::vec3 Bitangent;
	//};

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
		VertexArray VertexArray;
		DefaultMaterial Material;
		//std::vector<VertexData> Vertices;
		VertexData Vertices;
		std::vector<uint32_t> Indices;
		
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