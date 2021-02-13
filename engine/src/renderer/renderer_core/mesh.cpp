
#include "mesh.h"


namespace Bubble
{
	Mesh::Mesh(DefaultMaterial&& material,
			   VertexData&& vertices,
			   std::vector<uint32_t>&& indices)
		: mMaterial(std::move(material)),
		  mVertices(std::move(vertices)),
		  mIndices(std::move(indices))
	{
		BufferLayout layout
		{
			{ GLSLDataType::Float3, "Position",  mVertices.Positions.size()  },
			{ GLSLDataType::Float3, "Normal",    mVertices.Normals.size()    },
			{ GLSLDataType::Float2, "TexCoords", mVertices.TexCoords.size()  },
			{ GLSLDataType::Float3, "Tangent",   mVertices.Tangents.size()   },
			{ GLSLDataType::Float3, "Bitangent", mVertices.Bitangents.size() }
		};

		size_t size = sizeof(glm::vec3) * mVertices.Positions.size() + sizeof(glm::vec3) * mVertices.Normals.size() +
					  sizeof(glm::vec2) * mVertices.TexCoords.size() + sizeof(glm::vec3) * mVertices.Tangents.size() +
					  sizeof(glm::vec3) * mVertices.Bitangents.size();

		char* data = new char[size];
		size_t offset = 0;

		memmove(data, mVertices.Positions.data(), sizeof(glm::vec3) * mVertices.Positions.size());
		offset += sizeof(glm::vec3) * mVertices.Positions.size();

		memmove(data + offset, mVertices.Normals.data(),    sizeof(glm::vec3) * mVertices.Normals.size());
		offset += sizeof(glm::vec3) * mVertices.Normals.size();

		memmove(data + offset, mVertices.TexCoords.data(),  sizeof(glm::vec2) * mVertices.TexCoords.size());
		offset += sizeof(glm::vec2) * mVertices.TexCoords.size();

		memmove(data + offset, mVertices.Tangents.data(),   sizeof(glm::vec3) * mVertices.Tangents.size());
		offset += sizeof(glm::vec3) * mVertices.Tangents.size();

		memmove(data + offset, mVertices.Bitangents.data(), sizeof(glm::vec3) * mVertices.Bitangents.size());


		IndexBuffer  index_buffer = IndexBuffer(mIndices.data(), mIndices.size());
		VertexBuffer vertex_buffer = VertexBuffer (data, size);
		vertex_buffer.SetLayout(layout);

		mVertexArray.AddVertexBuffer(std::move(vertex_buffer));
		mVertexArray.SetIndexBuffer(std::move(index_buffer));
	}

}