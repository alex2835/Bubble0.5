#pragma once

#include "GL/glew.h"
#include <cstdint>
#include <cassert>]

namespace Bubble
{
	struct FramebufferSpecification
	{
		int Width, Height;
		int Samples = 1;
		bool SwapChainTarget = false;
	};

	struct Framebuffer
	{
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;

		Framebuffer() = default;
		Framebuffer(const FramebufferSpecification& spec);
		void Create(const FramebufferSpecification& spec);

		~Framebuffer();

		void Bind();
		void Unbind();
		void Invalidate();

		void Resize(uint32_t width, uint32_t height);

		uint32_t GetColorAttachmentRendererID();
		const FramebufferSpecification& GetSpecification() const;

		//static Framebuffer Create(const FramebufferSpecification& spec);
	};
}