#pragma once

#include "renderer/framebuffer.h"
#include <string>
#include <algorithm>

namespace Bubble
{
	struct Viewport;
	extern std::vector<Viewport*> sEditorViewports;

	/*
		Editor framebuffer abstraction
	*/

	struct Viewport : Framebuffer
	{
		std::string mName;
		glm::ivec2  mNewSize;

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