
#include "cubemap.h"


namespace Bubble
{
	Cubemap::Cubemap(int width, int height, const Texture2DSpecification& spec)
	{
		glGenTextures(1, &mRendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererID);

		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, spec.mInternalFormat,
				width, height, 0, spec.mDataFormat, GL_FLOAT, nullptr);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, spec.mMagFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, spec.mMinFiler);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	Cubemap::Cubemap(Cubemap&& other)
	{
		mRendererID = other.mRendererID;
		other.mRendererID = 0;
	}

	Cubemap& Cubemap::operator=(Cubemap&& other)
	{
		if (this != &other)
		{
			mRendererID = other.mRendererID;
			other.mRendererID = 0;
		}
		return *this;
	}


	Cubemap::Cubemap(const std::string& dir, const std::string& ext, const Texture2DSpecification& spec)
	{
		const char* names[] = { "/right", "/left", "/top", "/bottom", "/front", "/back" };
		glGenTextures(1, &mRendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererID);

		int width, height, chanels;
		unsigned char* data;

		for (GLuint i = 0; i < 6; i++)
		{
			std::string path = dir + names[i] + ext;
			data = stbi_load(path.c_str(), &width, &height, &chanels, 0);

			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
					width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				// Release resource
				glDeleteTextures(1, &mRendererID);
				throw std::runtime_error("Cubemap loading failed: " + path);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, spec.mMagFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, spec.mMinFiler);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	Cubemap::Cubemap(uint8_t* const data[6], const Texture2DSpecification& spec)
	{
		glGenTextures(1, &mRendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererID);

		for (GLuint i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, spec.mInternalFormat,
				spec.mWidth, spec.mHeight, 0, spec.mDataFormat, GL_UNSIGNED_BYTE, data[i]);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, spec.mMagFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, spec.mMinFiler);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	Cubemap::~Cubemap()
	{
		glDeleteTextures(1, &mRendererID);
	}

	void Cubemap::Bind(int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererID);
	}

}