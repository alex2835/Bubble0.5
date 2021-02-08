
#include "viewport.h"


namespace Bubble
{
    Viewport::Viewport(int width, int height, const std::string& name)
		: Framebuffer(width, height),
          mName(name),
          mNewSize(width, height)
	{

	}

	Viewport::Viewport(Viewport&& other) noexcept
		: Framebuffer(std::move(other))
	{
		mName = std::move(other.mName);
		mNewSize = other.mNewSize;
		other.mNewSize = glm::ivec2(0);
	}

    void Viewport::OnUpdate()
    {
		if (mNewSize != GetSize())
		{
			Resize(mNewSize);
		}
    }

    Viewport::~Viewport()
	{

	}

	Viewport& Viewport::operator=(Viewport&& other) noexcept
	{
		Framebuffer& fb = *this;
		fb = std::move(other);
		mName = std::move(other.mName);
		mNewSize = other.mNewSize;
		other.mNewSize = glm::ivec2(0);
		return *this;
	}

}