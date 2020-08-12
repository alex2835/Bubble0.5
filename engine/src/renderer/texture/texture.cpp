
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace Bubble {

	Texture2D::Texture2D(uint32_t width, uint32_t height, const Texture2DSpecification& spec)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = spec.InternalFormat;
		m_DataFormat = spec.DataFormat;

		glcall(glGenTextures(1, &m_RendererID));
		glcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		glcall(glTexImage2D(GL_TEXTURE_2D, 0, spec.InternalFormat, width, height, 0, spec.DataFormat, GL_UNSIGNED_BYTE, nullptr));
		
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, spec.MinFiler));
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, spec.MagFilter));
		
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, spec.WrapS));
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, spec.WrapT));

		if (spec.WrapS == GL_CLAMP_TO_BORDER || spec.WrapT == GL_CLAMP_TO_BORDER)
		{
			glcall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (float*)&spec.BorderColor));
		}
	}

	Texture2D::Texture2D(const std::string& path, const Texture2DSpecification& spec)
		: m_Path(path)
	{
		stbi_set_flip_vertically_on_load(spec.Flip);
		int width, height, channels;
		stbi_uc* data = nullptr;
		
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (data == nullptr)
		{
			throw std::runtime_error("Failed to load image!\nPath: " + path);
		}

		m_Width = width;
		m_Height = height;

		GLenum internal_format = 0, data_format = 0;
		if (channels == 1)
		{
			internal_format = GL_R8;
			data_format = GL_RED;
		}
		else if (channels == 3)
		{
			internal_format = GL_RGB8;
			data_format = GL_RGB;
		}
		else if (channels == 4)
		{
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
		}
		
		m_InternalFormat = internal_format;
		m_DataFormat = data_format;

		BUBBLE_CORE_ASSERT(internal_format & data_format, "Format not supported!");

		glcall(glGenTextures(1, &m_RendererID));
		glcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		glcall(glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data));
		
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, spec.MinFiler));
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, spec.MagFilter));

		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, spec.WrapS));
		glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, spec.WrapT));

		if (spec.WrapS == GL_CLAMP_TO_BORDER || spec.WrapT == GL_CLAMP_TO_BORDER)
		{
			glcall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (float*)&spec.BorderColor));
		}

		if (spec.MinMap)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(data);
	}

	Texture2D::Texture2D(Texture2D&& other) noexcept
		: m_Path(std::move(other.m_Path)),
		  m_Width(other.m_Width),
		  m_Height(other.m_Height),
		  m_DataFormat(other.m_DataFormat),
		  m_InternalFormat(other.m_InternalFormat)
	{
		other.m_Width = 0;
		other.m_Height = 0;
		other.m_RendererID = 0;
	}

	Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
	{
		glDeleteTextures(1, &m_RendererID);

		m_Path = std::move(other.m_Path);
		m_Width = other.m_Width;
		m_Height = other.m_Height;
		m_DataFormat = other.m_DataFormat;
		m_InternalFormat = other.m_InternalFormat;

		other.m_Width = 0;
		other.m_Height = 0;
		other.m_RendererID = 0;

		return *this;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = 0;
		if (m_DataFormat == GL_RGBA)
		{
			bpp = 4;
		}
		else if (m_DataFormat == GL_RGB)
		{
			bpp = 3;
		}
		else if (m_DataFormat == GL_RED)
		{
			bpp = 1;
		}

		BUBBLE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTexSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}