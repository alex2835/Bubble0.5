#pragma once

#include "framebuffer/framebuffer.h"
#include <string>


namespace Editor
{
	struct Viewport
	{
		std::string m_Name;
		Bubble::Framebuffer m_Framebuffer;

		Viewport() = default;
		Viewport(int width, int height, const std::string& name = "Viewport");
		
		Viewport(const Viewport&) = delete;
		Viewport& operator= (const Viewport&) = delete;
		
		Viewport(Viewport&& other);
		Viewport& operator= (Viewport&& other);

		void Bind();
		void Unbind();
		
		const glm::ivec2 GetSize() const;
		void Resize(const glm::ivec2& size);
	};
}