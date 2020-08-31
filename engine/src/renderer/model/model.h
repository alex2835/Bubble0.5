#pragma once

#include "mesh.h"
#include <vector>


namespace Bubble
{
	class Model
	{
	public:
		std::vector<Mesh> Meshes;
	
		Model() = default;
		
		Model(const Model&) = delete;
		Model& operator= (const Model&) = delete;

		Model(Model&&) = default;
		Model& operator= (Model&&) = default;
	};

}