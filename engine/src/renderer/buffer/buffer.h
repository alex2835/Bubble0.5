#pragma once

#include "renderer_base.h"

#include <vector>
#include <string>
#include <cassert>


namespace Bubble
{
	enum class GLSLDataType
	{
		None, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

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

		BUBBLE_CORE_ASSERT(false, "Unknown GLSLDataType!");
		return 0;
	}


	struct BufferElement
	{
	public:
		std::string Name;
		GLSLDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(GLSLDataType type, const std::string & name, bool normalized = false)
			: 
			Name(name),
			Type(type),
			Size(GLSLDataTypeSize(type)),
			Offset(0),
			Normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (Type)
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

			BUBBLE_CORE_ASSERT(false, "Unknown GLSLDataType!");
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
				element.Offset = offset;
				offset += element.Size;
			}
			m_Stride = offset;
		}
	};


	class VertexBuffer
	{
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Size = 0;
		BufferLayout m_Layout;

	public:
		VertexBuffer() = default;
		VertexBuffer(uint32_t size);
		VertexBuffer(void* vertices, uint32_t size);

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

		uint32_t GetSize() { return m_Size; }
	};

	
	class IndexBuffer
	{
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;

	public:
		IndexBuffer() = default;
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