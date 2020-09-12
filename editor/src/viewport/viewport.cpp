
#include "viewport.h"


namespace Bubble
{
	Viewport::Viewport(int width, int height, const std::string& name)
		: m_Name(name),
		  m_Size(width, height),
		  m_Capacity(width, height)
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
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		other.m_Size = glm::ivec2(0);
		other.m_Capacity = glm::ivec2(0);
	}

	Viewport& Viewport::operator=(Viewport&& other) noexcept
	{
		m_Framebuffer = std::move(other.m_Framebuffer);
		m_Name = std::move(other.m_Name);
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		other.m_Size = glm::ivec2(0);
		other.m_Capacity = glm::ivec2(0);
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
		// return m_Framebuffer.Size();
		return m_Size;
	}


	void Viewport::Resize(const glm::ivec2& size)
	{
		// Down scale
		if (m_Capacity.x > size.x * 1.5f || m_Capacity.y > size.y * 1.5f) {
			LOG_WARN("Old vewport size {} {}", m_Capacity.x, m_Capacity.y);
			LOG_ERROR("Vewport downsize {} {}", size.x, size.y);
			m_Capacity = size;
			m_Framebuffer.Resize(size);
		}
		// Up scale
		else if (m_Capacity.x * 1.5f < size.x || m_Capacity.y * 1.5f < size.y) {
			LOG_WARN("Old vewport size {} {}", m_Capacity.x, m_Capacity.y);
			LOG_INFO("Vewport upersize {} {}", size.x, size.y);
			m_Capacity = size;
			m_Framebuffer.Resize(size);
		}
		m_Size = size;
	}

	const std::string& Viewport::GetName() const
	{
		return m_Name;
	}

	void Viewport::SetName(const std::string& name)
	{
		m_Name = name;
	}

	Framebuffer& Viewport::GetFramebuffer()
	{
		return m_Framebuffer;
	}

}