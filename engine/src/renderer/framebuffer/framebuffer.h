#pragma once

#include "renderer_base.h"

#include "glm/glm.hpp"
#include <cstdint>
#include <cassert>


namespace Bubble
{
	struct FramebufferSpecification
	{
		glm::ivec2 Size;
		int Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;

	public:
		Framebuffer() = default;
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator= (const Framebuffer&) = delete;

		Framebuffer(Framebuffer&& other) noexcept;
		Framebuffer& operator = (Framebuffer&& other) noexcept;

		Framebuffer(const FramebufferSpecification& spec);
		void Create(const FramebufferSpecification& spec);

		~Framebuffer();

		void Bind() const;
		void Unbind() const;
		void Invalidate();

		int GetWidth() const;
		int GetHeight() const;
		glm::ivec2 Size() const;
		void Resize(const glm::ivec2& size);

		uint32_t GetColorAttachmentRendererID();
		const FramebufferSpecification& GetSpecification() const;

		static void BindDefault();
	};
}