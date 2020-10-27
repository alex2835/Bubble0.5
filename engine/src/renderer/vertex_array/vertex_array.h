#pragma once

#include "buffer/buffer.h"

namespace Bubble
{
	class VertexArray
	{
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<VertexBuffer> m_VertexBuffers;
		IndexBuffer m_IndexBuffer;

	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&&);
		VertexArray& operator=(VertexArray&&);


		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(VertexBuffer&& vertexBuffer);
		void SetIndexBuffer(IndexBuffer&& indexBuffer);

		const uint32_t GetID() const { return m_RendererID; }
		const std::vector<VertexBuffer>& GetVertexBuffers() const;
		const IndexBuffer& GetIndexBuffer() const;
		void VertexBufferIndex(uint32_t val) { m_VertexBufferIndex = val; }
	};

}
