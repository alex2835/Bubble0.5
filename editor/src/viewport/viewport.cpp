
#include "viewport.h"


namespace Bubble
{
	Viewport::Viewport(int width, int height, const std::string& name)
		: Framebuffer({ { width, height } }),
		  Name(name),
		  Size(width, height),
		  Capacity(width, height)
	{}

	Viewport::Viewport(Viewport&& other) noexcept
		: Framebuffer(std::move(other))
	{
		Name = std::move(other.Name);
		Size = other.Size;
		Capacity = other.Capacity;
		other.Size = glm::ivec2(0);
		other.Capacity = glm::ivec2(0);
	}

	Viewport& Viewport::operator=(Viewport&& other) noexcept
	{
		Framebuffer& fb = *this;
		fb = std::move(other);
		Name = std::move(other.Name);
		Size = other.Size;
		Capacity = other.Capacity;
		other.Size = glm::ivec2(0);
		other.Capacity = glm::ivec2(0);
		return *this;
	}

	void Viewport::Resize(const glm::ivec2& size)
	{
		// Down scale
		if (Capacity.x > size.x * 1.5f || Capacity.y > size.y * 1.5f)
		{
			Capacity = size;
			Framebuffer::Resize(size);
		}
		// Up scale
		else if (Capacity.x * 1.5f < size.x || Capacity.y * 1.5f < size.y)
		{
			Capacity = size;
			Framebuffer::Resize(size);
		}
		Size = size;
	}

	Viewport::operator Framebuffer& ()
	{
		return *(Framebuffer*)this;
	}

	const glm::ivec2& Viewport::GetSize() const
	{
		return Size;
	}

	float Viewport::GetWidth()
	{
		return Size.x;
	}

	float Viewport::GetHeight()
	{
		return Size.y;
	}

}