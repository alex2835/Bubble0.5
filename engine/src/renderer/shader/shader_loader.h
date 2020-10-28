#pragma once

#include "shader.h"

namespace Bubble
{
	struct ShaderLoader
	{
		static std::vector<std::pair<std::string, Ref<Shader>>> LoadedShaders;

		static Ref<Shader> Load(const std::string& path);
		
		// Load shaders from file
		static Ref<Shader> Load(const std::string& name,
								const std::string& vertex,
								const std::string& fragment,
								const std::string& geometry = std::string());



	private:
		static void ParseShaders(const std::string& path, std::string& vertex, std::string& fragment, std::string& geometry);
		static Shader&& CompileShaders(const std::string& vertex_source, const std::string& fragment_source, const std::string& geometry_source);

	};
}