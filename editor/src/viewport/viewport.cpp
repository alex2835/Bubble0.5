
#include "viewport.h"


namespace Bubble
{
	std::vector<Viewport*> EditorViewports;

	Viewport::Viewport(int width, int height, const std::string& name)
		: Framebuffer(width, height),
		Name(name),
		NewSize(width, height)
	{
		Framebuffer::Resize({width, height});
		EditorViewports.push_back(this);
	}

	Viewport::Viewport(Viewport&& other) noexcept
		: Framebuffer(std::move(other))
	{
		Name = std::move(other.Name);
		NewSize = other.NewSize;
		other.NewSize = glm::ivec2(0);
	}

	Viewport::~Viewport()
	{
		auto iterator = std::find(EditorViewports.begin(), EditorViewports.end(), this);
		EditorViewports.erase(iterator);
	}

	Viewport& Viewport::operator=(Viewport&& other) noexcept
	{
		Framebuffer& fb = *this;
		fb = std::move(other);
		Name = std::move(other.Name);
		NewSize = other.NewSize;
		other.NewSize = glm::ivec2(0);
		return *this;
	}

}