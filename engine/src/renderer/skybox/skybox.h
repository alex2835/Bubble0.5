#pragma once

#include "cubemap/cubemap.h"
#include "vertex_array/vertex_array.h"


namespace Bubble
{
	struct Skybox
	{
		static VertexArray* sVertexArray;
		static void InitVertexArray();

		Cubemap mSkybox;

		Skybox() = default;

		Skybox(const Skybox&) = delete;
		Skybox& operator=(const Skybox&) = delete;

		Skybox(Skybox&&) = default;
		Skybox& operator=(Skybox&&) = default;

		void Bind(int slot = 0);
	};
}