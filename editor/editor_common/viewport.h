#pragma once

#include "framebuffer.h"
#include <string>

namespace Bubble
{
	struct Viewport : Framebuffer
	{
		std::string mName;
		glm::ivec2  mNewSize;

	public:
        Viewport() = default;

        Viewport(int width, int height, const std::string& name = "Viewport")
            : Framebuffer(width, height),
              mName(name),
              mNewSize(width, height)
        {}

        Viewport(const Viewport&) = delete;
        Viewport& operator= (const Viewport&) = delete;

        Viewport(Viewport&& other) noexcept
            : Framebuffer(std::move(other))
        {
            mName = std::move(other.mName);
            mNewSize = other.mNewSize;
            other.mNewSize = glm::ivec2(0);
        }

        void OnUpdate()
        {
            if (mNewSize != GetSize())
            {
                Resize(mNewSize);
            }
        }

        ~Viewport()
        {}

        Viewport& operator=(Viewport&& other) noexcept
        {
            Framebuffer& fb = *this;
            fb = std::move(other);
            mName = std::move(other.mName);
            mNewSize = other.mNewSize;
            other.mNewSize = glm::ivec2(0);
            return *this;
        }
	};

}