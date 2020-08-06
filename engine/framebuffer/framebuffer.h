#pragma once

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

	struct Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator= (const Framebuffer&) = delete;

		Framebuffer(Framebuffer&& other) noexcept;
		Framebuffer& operator = (Framebuffer&& other) noexcept;

		Framebuffer(const FramebufferSpecification& spec);
		void Create(const FramebufferSpecification& spec);

		~Framebuffer();

		void Bind();
		void Unbind();
		void Invalidate();

		const glm::ivec2& Size() const;
		void Resize(const glm::ivec2& size);

		uint32_t GetColorAttachmentRendererID();
		const FramebufferSpecification& GetSpecification() const;

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}