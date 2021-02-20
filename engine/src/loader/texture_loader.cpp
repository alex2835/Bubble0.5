
#include "loader.h"

namespace Bubble
{
    Ref<Texture2D> Loader::LoadTexture2DSingleColor(const std::string& name, const glm::vec4& color)
    {
        if (mLoadedTextures.count(name))
        {
            return mLoadedTextures[name];
        }
        Ref<Texture2D> texture = CreateRef<Texture2D>(color);
        mLoadedTextures[name] = texture;
        return texture;
    }

    Ref<Texture2D> Loader::LoadTexture2D(std::string path, const Texture2DSpecification& spec)
    {
        if (mLoadedTextures.count(path))
        {
            return mLoadedTextures[path];
        }

        Ref<Texture2D> texture = CreateRef<Texture2D>();
        mLoadedTextures[path] = texture;
        texture->mSpecification = spec;

        stbi_uc* data = nullptr;
        int width, height, channels;
        stbi_set_flip_vertically_on_load(spec.mFlip);
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        
        if (data == nullptr)
            throw std::runtime_error("Failed to load image!\nPath: " + path);

        texture->mSpecification.mWidth  = width;
        texture->mSpecification.mHeight = height;
        SetTextureSpecChanels(texture->mSpecification, channels);
        texture->mSpecification.mAnisotropicFiltering = true;

        texture->Invalidate();
        texture->SetData(data, width * height * channels);
        stbi_image_free(data);
        return texture;
    }

    std::tuple<Scope<uint8_t[]>, Texture2DSpecification>
        Loader::OpenRawImage(const std::string& path, Texture2DSpecification spec)
    {
        uint8_t* data = nullptr;
        int width, height, channels;

        stbi_set_flip_vertically_on_load(spec.mFlip);
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (data == nullptr)
            throw std::runtime_error("Failed to load image!\nPath: " + path);

        spec.mWidth = width;
        spec.mHeight = height;
        SetTextureSpecChanels(spec, channels);

        return { Scope<uint8_t[]>(data), spec };
    }

    // Skysphere texture
    Ref<Texture2D> Loader::LoadSkysphere(const std::string& path)
    {
        if (mLoadedSkypsheres.count(path))
        {
            return mLoadedSkypsheres[path];
        }
        mLoadedSkypsheres[path] = LoadTexture2D(path);
        return mLoadedSkypsheres[path];
    }
}