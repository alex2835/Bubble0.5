#pragma once

#include "buffer/buffer.h"

namespace Bubble
{
	class VertexArray
	{
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&&);
		VertexArray& operator=(VertexArray&&);


		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

		const uint32_t GetID() const { return m_RendererID; }
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const;
		const Ref<IndexBuffer>& GetIndexBuffer() const;
	};

}
