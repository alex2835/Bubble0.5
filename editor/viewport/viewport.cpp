
#include "viewport.h"


namespace Editor
{
	Viewport::Viewport(int width, int height, const std::string& name)
		:
		m_Name(name)
	{
		Bubble::FramebufferSpecification spec;
		spec.Samples = 1;
		spec.Size = { width, height };
		m_Framebuffer.Create(spec);
	}

	Viewport::Viewport(Viewport&& other) noexcept
	{
		m_Framebuffer = std::move(other.m_Framebuffer);
		m_Name = std::move(other.m_Name);
	}

	Viewport& Viewport::operator=(Viewport&& other) noexcept
	{
		m_Framebuffer = std::move(other.m_Framebuffer);
		m_Name = std::move(other.m_Name);
		return *this;
	}

	void Viewport::Bind()
	{
		m_Framebuffer.Bind();
	}

	void Viewport::Unbind()
	{
		m_Framebuffer.Unbind();
	}

	const glm::ivec2 Viewport::Size() const
	{
		return m_Framebuffer.Size();
	}
	void Viewport::Resize(const glm::ivec2& size)
	{
		m_Framebuffer.Resize(size);
	}

	const std::string& Viewport::GetName() const
	{
		return m_Name;
	}

	void Viewport::Rename(const std::string& new_name)
	{
		m_Name = new_name;
	}

	Bubble::Framebuffer& Viewport::GetFramebuffer()
	{
		return m_Framebuffer;
	}

}