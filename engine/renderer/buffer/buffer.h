#pragma once

#include "base.h"

#include <vector>
#include <string>
#include <cassert>


namespace Bubble
{
	enum class GLSLDataType
	{
		None, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	inline GLenum GLSLDataTypeToOpenGLBaseType(GLSLDataType type)
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

		assert("Unknown ShaderDataType!");
		return 0;
	}

	static uint32_t GLSLDataTypeSize(GLSLDataType type)
	{
		switch (type)
		{
		case GLSLDataType::Float:    return 4;
		case GLSLDataType::Float2:   return 4 * 2;
		case GLSLDataType::Float3:   return 4 * 3;
		case GLSLDataType::Float4:   return 4 * 4;
		case GLSLDataType::Mat3:     return 4 * 3 * 3;
		case GLSLDataType::Mat4:     return 4 * 4 * 4;
		case GLSLDataType::Int:      return 4;
		case GLSLDataType::Int2:     return 4 * 2;
		case GLSLDataType::Int3:     return 4 * 3;
		case GLSLDataType::Int4:     return 4 * 4;
		case GLSLDataType::Bool:     return 1;
		}

		assert("Unknown GLSLDataType!");
		return 0;
	}


	class BufferElement
	{
	public:
		std::string m_Name;
		GLSLDataType m_Type;
		uint32_t m_Size;
		size_t m_Offset;
		bool m_Normalized;

		BufferElement() = default;

		BufferElement(GLSLDataType type, const std::string & name, bool normalized = false)
			: 
			m_Name(name),
			m_Type(type),
			m_Size(GLSLDataTypeSize(type)),
			m_Offset(0),
			m_Normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (m_Type)
			{
				case GLSLDataType::Float:   return 1;
				case GLSLDataType::Float2:  return 2;
				case GLSLDataType::Float3:  return 3;
				case GLSLDataType::Float4:  return 4;
				case GLSLDataType::Mat3:    return 3; // 3* float3
				case GLSLDataType::Mat4:    return 4; // 4* float4
				case GLSLDataType::Int:     return 1;
				case GLSLDataType::Int2:    return 2;
				case GLSLDataType::Int3:    return 3;
				case GLSLDataType::Int4:    return 4;
				case GLSLDataType::Bool:    return 1;
			}

			assert("Unknown GLSLDataType!");
			return 0;
		}
	};


	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.m_Offset = offset;
				offset += element.m_Size;
			}
			m_Stride = offset;
		}
	};


	class VertexBuffer
	{
	private:
		uint32_t m_RendererID = 0;
		BufferLayout m_Layout;

	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(float* vertices, uint32_t size);

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&&) noexcept;
		VertexBuffer& operator=(VertexBuffer&&) noexcept;

		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, uint32_t size);
		 
		const BufferLayout& GetLayout() const;
		void SetLayout(const BufferLayout& layout);
	};

	
	class IndexBuffer
	{
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;

	public:
		IndexBuffer(uint32_t* indices, uint32_t count);

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer &&) noexcept;
		IndexBuffer& operator=(IndexBuffer&&) noexcept;

		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetCount() const;
	};
}