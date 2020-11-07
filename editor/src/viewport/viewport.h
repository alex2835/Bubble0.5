#pragma once

#include "framebuffer/framebuffer.h"

#include <string>
#include <algorithm>

namespace Bubble
{
	struct Viewport;
	extern std::vector<Viewport*> EditorViewports;

	/*
		Editor framebuffer abstraction
	*/

	struct Viewport : Framebuffer
	{
		std::string Name;
		glm::ivec2 NewSize;

	public:
		Viewport() = default;
		Viewport(int width, int height, const std::string& name = "Viewport");
		
		Viewport(const Viewport&) = delete;
		Viewport& operator= (const Viewport&) = delete;
		
		Viewport(Viewport&& other) noexcept;
		Viewport& operator= (Viewport&& other) noexcept;

		~Viewport();
	};

}