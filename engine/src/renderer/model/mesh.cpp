
#include "mesh.h"


namespace Bubble
{
	Mesh::Mesh(DefaultMaterial&& material,
			   VertexData&& vertices,
			   std::vector<uint32_t>&& indices)
		: Material(std::move(material)),
		  Vertices(std::move(vertices)),
		  Indices(std::move(indices))
	{
		BufferLayout layout
		{
			{ GLSLDataType::Float3, "Position",  Vertices.Positions.size()  },
			{ GLSLDataType::Float3, "Normal",    Vertices.Normals.size()    },
			{ GLSLDataType::Float2, "TexCoords", Vertices.TexCoords.size()  },
			{ GLSLDataType::Float3, "Tangent",   Vertices.Tangents.size()   },
			{ GLSLDataType::Float3, "Bitangent", Vertices.Bitangents.size() }
		};

		size_t size = sizeof(glm::vec3) * Vertices.Positions.size() + sizeof(glm::vec3) * Vertices.Normals.size() +
					  sizeof(glm::vec2) * Vertices.TexCoords.size() + sizeof(glm::vec3) * Vertices.Tangents.size() +
					  sizeof(glm::vec3) * Vertices.Bitangents.size();

		char* data = new char[size];
		size_t offset = 0;

		memmove(data, Vertices.Positions.data(), sizeof(glm::vec3) * Vertices.Positions.size());
		offset += sizeof(glm::vec3) * Vertices.Positions.size();

		memmove(data + offset, Vertices.Normals.data(),    sizeof(glm::vec3) * Vertices.Normals.size());
		offset += sizeof(glm::vec3) * Vertices.Normals.size();

		memmove(data + offset, Vertices.TexCoords.data(),  sizeof(glm::vec2) * Vertices.TexCoords.size());
		offset += sizeof(glm::vec2) * Vertices.TexCoords.size();

		memmove(data + offset, Vertices.Tangents.data(),   sizeof(glm::vec3) * Vertices.Tangents.size());
		offset += sizeof(glm::vec3) * Vertices.Tangents.size();

		memmove(data + offset, Vertices.Bitangents.data(), sizeof(glm::vec3) * Vertices.Bitangents.size());


		IndexBuffer  index_buffer = IndexBuffer(Indices.data(), Indices.size());
		VertexBuffer vertex_buffer = VertexBuffer (data, size);
		vertex_buffer.SetLayout(layout);

		VertexArray.AddVertexBuffer(std::move(vertex_buffer));
		VertexArray.SetIndexBuffer(std::move(index_buffer));
	}

}