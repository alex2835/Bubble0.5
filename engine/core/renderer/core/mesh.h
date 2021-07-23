#pragma once

#include "buffer.h"
#include "texture.h"
#include "vertex_array.h"
#include "material.h"

#include "glm/glm.hpp"
#include <vector>


namespace Bubble
{
	struct VertexData
	{
		std::vector<glm::vec3> mPositions;
		std::vector<glm::vec3> mNormals;
		std::vector<glm::vec2> mTexCoords;
		std::vector<glm::vec3> mTangents;
		std::vector<glm::vec3> mBitangents;
	};


	struct Mesh
	{
		std::string			  mName;
		VertexArray           mVertexArray;
		DefaultMaterial       mMaterial;
		VertexData            mVertices;
		std::vector<uint32_t> mIndices;
		
		Mesh() = default;
		Mesh(const std::string& name,
			 DefaultMaterial&& Material,
			 VertexData&& vertices,
			 std::vector<uint32_t>&& indices);

		Mesh(const Mesh&) = delete;
		Mesh& operator= (const Mesh&) = delete;

		Mesh(Mesh&&) = default;
		Mesh& operator= (Mesh&&) = default;
	};

}