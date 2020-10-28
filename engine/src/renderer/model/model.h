#pragma once

#include "mesh.h"
#include "glm-aabb/AABB.hpp"

#include <vector>


namespace Bubble
{
	class Model
	{
	public:
		std::vector<Mesh> mMeshes;
		AABB mBoundingBox;

		Model() = default;
		
		Model(const Model&) = delete;
		Model& operator= (const Model&) = delete;

		Model(Model&&) = default;
		Model& operator= (Model&&) = default;

		void CreateBoundingBox();
		AABB TransformBoundingBox(const glm::mat4& transform);
	};

}