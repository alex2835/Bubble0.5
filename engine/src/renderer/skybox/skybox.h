#pragma once

#include "cubemap/cubemap.h"
#include "vertex_array/vertex_array.h"


namespace Bubble
{
	class Skybox
	{
		static VertexArray* s_VertexArray;
	public:
		Cubemap mSkybox;

		Skybox() = default;
		Skybox(const std::string& dir, const std::string& ext);
		Skybox(const std::string& file);

		Skybox(const Skybox&) = delete;
		Skybox& operator=(const Skybox&) = delete;

		Skybox(Skybox&&) = default;
		Skybox& operator=(Skybox&&) = default;

		void Bind(int slot = 0);

		// Directory with (top.png, bot.png, ...)
		static Skybox LoadFromDir(const std::string& dir, const std::string& ext = ".jpg");
		// Single file skybox
		static Skybox LoadFromFile(const std::string& file);

	private:
		static void InitVertexArray();
	};
}