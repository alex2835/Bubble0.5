
#include "buffer.h"

namespace Bubble
{
	// ==================== Vertex buffer ======================

	VertexBuffer::VertexBuffer(uint32_t size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	{
		m_RendererID = other.m_RendererID;
		m_Layout = std::move(other.m_Layout);
		other.m_RendererID = 0;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		m_RendererID = other.m_RendererID;
		m_Layout = std::move(other.m_Layout);
		other.m_RendererID = 0;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
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
	{
		glGenBuffers(1, &m_RendererID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
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
		}
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t IndexBuffer::GetCount() const
	{
		return m_Count;
	}

}
