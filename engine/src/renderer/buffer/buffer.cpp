
#include "buffer.h"


namespace Bubble
{
	// ==================== Vertex buffer ======================

	VertexBuffer::VertexBuffer(uint32_t size)
		: m_Size(size)
	{
		glcall(glGenBuffers(1, &m_RendererID));
		glcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glcall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	VertexBuffer::VertexBuffer(void* vertices, uint32_t size)
		: m_Size(size)
	{
		glcall(glGenBuffers(1, &m_RendererID));
		glcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glcall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	{
		m_RendererID = other.m_RendererID;
		m_Layout = std::move(other.m_Layout);
		m_Size = other.m_Size;
		other.m_RendererID = 0;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		m_RendererID = other.m_RendererID;
		m_Layout = std::move(other.m_Layout);
		m_Size = other.m_Size;
		other.m_RendererID = 0;
		other.m_Size = 0;
		return *this;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const
	{
		glcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const
	{
		glcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glcall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}

	const Bubble::BufferLayout& VertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}


	// ===================== Index buffer ======================== 

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glcall(glGenBuffers(1, &m_RendererID));
		glcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		glcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	{
		m_RendererID = other.m_RendererID;
		m_Count = other.m_Count;
		other.m_RendererID = 0;
		other.m_Count = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			m_RendererID = other.m_RendererID;
			m_Count = other.m_Count;
			other.m_RendererID = 0;
			other.m_Count = 0;
			return *this;
		}
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const
	{
		glcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() const
	{
		glcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	uint32_t IndexBuffer::GetCount() const
	{
		return m_Count;
	}

}
