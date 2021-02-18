
#include "framebuffer.h"

namespace Bubble
{
    Framebuffer::Framebuffer(const FramebufferSpecification& spec)
        : mSpecification(spec)
    {
        SetDefaultAttachemtSpec();
        Invalidate();
    }

    Framebuffer::Framebuffer(uint32_t width, uint32_t height)
        : mSpecification({ width, height })
    {
        SetDefaultAttachemtSpec();
        Invalidate();
    }

    Framebuffer::Framebuffer(Texture2D&& color, Texture2D&& depth)
        : mColorAttachment(std::move(color)),
          mDepthAttachment(std::move(depth))
    {
        mSpecification = { mColorAttachment.GetWidth(), mColorAttachment.GetHeight() };
        Invalidate();
    }

    Framebuffer::Framebuffer(Framebuffer&& other) noexcept
    {
        mRendererID    = other.mRendererID;
        mSpecification = other.mSpecification;
        mColorAttachment = std::move(other.mColorAttachment);
        mDepthAttachment = std::move(other.mDepthAttachment);
        other.mRendererID = 0;
    }

    Framebuffer& Framebuffer::operator= (Framebuffer&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteFramebuffers(1, &mRendererID);
            mRendererID    = other.mRendererID;
            mSpecification = other.mSpecification;
            mColorAttachment = std::move(other.mColorAttachment);
            mDepthAttachment = std::move(other.mDepthAttachment);
            other.mRendererID = 0;
        }
        return *this;
    }

    void Framebuffer::Create(const FramebufferSpecification& spec)
    {
        mSpecification = spec;
        SetDefaultAttachemtSpec();
        Invalidate();
    }

    void Framebuffer::SetColorAttachment(Texture2D&& texture)
    {
        mColorAttachment = std::move(texture);
    }

    void Framebuffer::SetDepthAttachment(Texture2D&& texture)
    {
        mDepthAttachment = std::move(texture);
    }

    Texture2D Framebuffer::GetColorAttachment()
    {
        return std::move(mColorAttachment);
    }

    Texture2D Framebuffer::GetDepthAttachment()
    {
        return std::move(mDepthAttachment);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &mRendererID);
    }

    void Framebuffer::Invalidate()
    {
        glDeleteFramebuffers(1, &mRendererID);
        glcall(glGenFramebuffers(1, &mRendererID));
        glcall(glBindFramebuffer(GL_FRAMEBUFFER, mRendererID));

        if (mColorAttachment.GetWidth()  != mSpecification.mWidth ||
            mColorAttachment.GetHeight() != mSpecification.mHeight)
        {
            mColorAttachment.Resize({ mSpecification.mWidth, mSpecification.mHeight });
        }

        if  (mDepthAttachment.GetWidth() != mSpecification.mWidth ||
             mDepthAttachment.GetHeight() != mSpecification.mHeight)
        {
            mDepthAttachment.Resize({ mSpecification.mWidth, mSpecification.mHeight });
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GetColorAttachmentRendererID(), 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, GetDepthAttachmentRendererID(), 0);

        BUBBLE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    int Framebuffer::GetWidth() const
    {
        return mSpecification.mWidth;
    }

    int Framebuffer::GetHeight() const
    {
        return mSpecification.mHeight;
    }

    void Framebuffer::Bind() const
    {
        glcall(glBindFramebuffer(GL_FRAMEBUFFER, mRendererID));
        glViewport(0, 0, GetWidth(), GetHeight());
    }

    void Framebuffer::Unbind() const
    {
        glcall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    void Framebuffer::BindWindow(Window* window)
    {
        glcall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        glm::ivec2 window_size = window->GetSize();
        glViewport(0, 0, window_size.x, window_size.y);
    }

    const glm::ivec2& Framebuffer::GetSize() const
    {
        return { GetWidth(), GetHeight() };
    }

    void Framebuffer::Resize(glm::ivec2 size)
    {
        // Prevent framebuffer error
        mSpecification.mWidth  = std::max(1, size.x);
        mSpecification.mHeight = std::max(1, size.y);
        Invalidate();
    }

    void Framebuffer::Resize(uint32_t width, uint32_t height)
    {
        if (width < 0 || height < 0)
        {
            LOG_CORE_ERROR("Invalid framebuffer resize params width: {} height: {}", width, height);
            return;
        }
        mSpecification.mWidth = width;
        mSpecification.mHeight = height;
        Invalidate();
    }

    const FramebufferSpecification& Framebuffer::GetSpecification() const
    {
        return mSpecification;
    }

    uint32_t Framebuffer::GetColorAttachmentRendererID()
    {
        return mColorAttachment.GetRendererID();
    }

    uint32_t Framebuffer::GetDepthAttachmentRendererID()
    {
        return mDepthAttachment.GetRendererID();

    }

    void Framebuffer::SetDefaultAttachemtSpec()
    {
        mDepthAttachment.mSpecification.mChanelFormat = GL_FLOAT;
        mDepthAttachment.mSpecification.mDataFormat   = GL_DEPTH_COMPONENT;
        mDepthAttachment.mSpecification.mInternalFormat = GL_DEPTH_COMPONENT;
        mDepthAttachment.mSpecification.mWrapS = GL_CLAMP_TO_BORDER;
        mDepthAttachment.mSpecification.mWrapT = GL_CLAMP_TO_BORDER;
    }

    
}

