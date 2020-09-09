#pragma once

#include "cubemap/cubemap.h"
#include "vertex_array/vertex_array.h"


namespace Bubble
{
	class Skybox
	{
		static VertexArray* s_VertexArray;
	public:
		Cubemap m_Skybox;

		Skybox(const std::string& dir, const std::string& ext = ".jpg");
		void Bind(int slot = 0);
	};
}