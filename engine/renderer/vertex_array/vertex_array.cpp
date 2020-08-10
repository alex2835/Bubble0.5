
#include "vertex_array.h"

namespace Bubble
{
	static GLenum GLSLDataTypeToOpenGLBaseType(GLSLDataType type)
	{
		switch (type)
		{
			case GLSLDataType::Float:    return GL_FLOAT;
			case GLSLDataType::Float2:   return GL_FLOAT;
			case GLSLDataType::Float3:   return GL_FLOAT;
			case GLSLDataType::Float4:   return GL_FLOAT;
			case GLSLDataType::Mat3:     return GL_FLOAT;
			case GLSLDataType::Mat4:     return GL_FLOAT;
			case GLSLDataType::Int:      return GL_INT;
			case GLSLDataType::Int2:     return GL_INT;
			case GLSLDataType::Int3:     return GL_INT;
			case GLSLDataType::Int4:     return GL_INT;
			case GLSLDataType::Bool:     return GL_BOOL;
		}

		BUBBLE_CORE_ASSERT(false, "Unknown GLSLDataType!");
		return 0;
	}

	VertexArray::VertexArray()
	{
		glcall(glGenVertexArrays(1, &m_RendererID));
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const
	{
		glcall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const
	{
		glcall(glBindVertexArray(0));
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		BUBBLE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glcall(glBindVertexArray(m_RendererID));
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case GLSLDataType::Float:
				case GLSLDataType::Float2:
				case GLSLDataType::Float3:
				case GLSLDataType::Float4:
				case GLSLDataType::Int:
				case GLSLDataType::Int2:
				case GLSLDataType::Int3:
				case GLSLDataType::Int4:
				case GLSLDataType::Bool:
				{
					glcall(glEnableVertexAttribArray(m_VertexBufferIndex));
					glcall(glVertexAttribPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						GLSLDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset));
					m_VertexBufferIndex++;
					break;
				}
				case GLSLDataType::Mat3:
				case GLSLDataType::Mat4:
				{
					uint32_t count = element.GetComponentCount();
					for (uint32_t i = 0; i < count; i++)
					{
						glcall(glEnableVertexAttribArray(m_VertexBufferIndex));
						glcall(glVertexAttribPointer(m_VertexBufferIndex,
							count,
							GLSLDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(sizeof(float) * count * i)));
						glcall(glVertexAttribDivisor(m_VertexBufferIndex, 1));
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					BUBBLE_CORE_ASSERT(false, "Unknown GLSLDataType!");
			}
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glcall(glBindVertexArray(m_RendererID));
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}
