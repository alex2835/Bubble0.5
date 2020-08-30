
#include "mesh.h"


namespace Bubble
{
	Mesh::Mesh(const Ref<std::vector<Vertex>>& vertices,
			   const Ref<std::vector<uint32_t>>& indices,
			   const Ref<std::vector<MeshTexture>>& textures)
		: Vertices(vertices),
		  Indices(indices),
		  Textures(textures)
	{
		BufferLayout layout
		{
			{ GLSLDataType::Float3, "Position" },
			{ GLSLDataType::Float3, "Normal" },
			{ GLSLDataType::Float2, "TexCoords" },
			{ GLSLDataType::Float3, "Tangent" },
			{ GLSLDataType::Float3, "Bitangent" }
		};

		auto vertex_buffer = CreateRef<VertexBuffer>(Vertices->data(), sizeof(Vertex) * Vertices->size());
		vertex_buffer->SetLayout(layout);

		auto index_buffer = CreateRef<IndexBuffer>(Indices->data(), Indices->size());

		VertexArray.AddVertexBuffer(vertex_buffer);
		VertexArray.SetIndexBuffer(index_buffer);
	}

}