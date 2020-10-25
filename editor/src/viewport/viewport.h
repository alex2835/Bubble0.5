#pragma once

#include "framebuffer/framebuffer.h"

#include <string>


namespace Bubble
{
	struct Viewport : public Framebuffer
	{
		std::string Name;
		glm::ivec2 Size;
		glm::ivec2 Capacity;

	public:
		Viewport() = default;
		Viewport(int width, int height, const std::string& name = "Viewport");
		
		Viewport(const Viewport&) = delete;
		Viewport& operator= (const Viewport&) = delete;
		
		Viewport(Viewport&& other) noexcept;
		Viewport& operator= (Viewport&& other) noexcept;

		void Resize(const glm::ivec2& size);
		const glm::ivec2& GetSize() const;
		float GetWidth();
		float GetHeight();

		operator Framebuffer& ();
	};
}