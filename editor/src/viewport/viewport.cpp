
#include "viewport.h"


namespace Bubble
{
	std::vector<Viewport*> sEditorViewports;

	Viewport::Viewport(int width, int height, const std::string& name)
		: Framebuffer(width, height),
          mName(name),
          mNewSize(width, height)
	{
		sEditorViewports.push_back(this);
	}

	Viewport::Viewport(Viewport&& other) noexcept
		: Framebuffer(std::move(other))
	{
		mName = std::move(other.mName);
		mNewSize = other.mNewSize;
		other.mNewSize = glm::ivec2(0);
	}

	Viewport::~Viewport()
	{
		auto iterator = std::ranges::find(sEditorViewports, this);
		sEditorViewports.erase(iterator);
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