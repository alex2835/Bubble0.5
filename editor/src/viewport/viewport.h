#pragma once

#include "framebuffer/framebuffer.h"

#include <string>


namespace Bubble
{
	class Viewport
	{
		std::string m_Name;
		Framebuffer m_Framebuffer;
		glm::ivec2 m_Size;
		glm::ivec2 m_Capacity;

	public:
		Viewport() = default;
		Viewport(int width, int height, const std::string& name = "Viewport");
		
		Viewport(const Viewport&) = delete;
		Viewport& operator= (const Viewport&) = delete;
		
		Viewport(Viewport&& other) noexcept;
		Viewport& operator= (Viewport&& other) noexcept;

		void Bind();
		void Unbind();
		
		const glm::ivec2 Size() const;
		void Resize(const glm::ivec2& size);

		const std::string& GetName() const;
		void SetName(const std::string& name);

		Framebuffer& GetFramebuffer();
	};
}