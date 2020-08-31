#pragma once

#include "mesh.h"
#include <vector>


namespace Bubble
{
	class Model
	{
		std::vector<Mesh> m_Meshes;
	
	public:
		Model() = default;
		Model(Model&&) = default;
		Model& operator= (Model&&) = default;

		const std::vector<Mesh>& GetMeshes() { return m_Meshes; }
	};

}