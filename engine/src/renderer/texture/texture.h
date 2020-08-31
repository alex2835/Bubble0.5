#pragma once

#include "renderer_base.h"
#include "glm/vec4.hpp"


namespace Bubble
{
	struct Texture2DSpecification
	{
		uint32_t InternalFormat = GL_RGBA8;
		uint32_t DataFormat = GL_RGBA;
		uint32_t MinFiler = GL_LINEAR;
		uint32_t MagFilter = GL_NEAREST;
		uint32_t WrapS = GL_REPEAT;
		uint32_t WrapT = GL_REPEAT;
		glm::vec4 BorderColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		bool Flip = false;
		bool MinMap = true;
	};

	class Texture2D
	{
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		uint32_t m_RendererID = 0;
		uint32_t m_InternalFormat = 0, m_DataFormat = 0;

	public:
		Texture2D(uint32_t width, uint32_t height, const Texture2DSpecification& spec = {});
		Texture2D(const std::string& path, const Texture2DSpecification& spec = {});

		Texture2D(const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;

		Texture2D(Texture2D&&) noexcept;
		Texture2D& operator= (Texture2D&&) noexcept;

		~Texture2D();

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetRendererID() const  { return m_RendererID; }

		void SetData(void* data, uint32_t size);

		void Bind(uint32_t slot = 0) const;
		static void UnbindAll() { glActiveTexture(GL_TEXTURE0); }

		bool operator==(const Texture2D& other) const
		{
			return m_RendererID == other.m_RendererID;
		}
	};
}