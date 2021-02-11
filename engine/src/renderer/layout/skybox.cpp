
#include "skybox.h"


namespace Bubble
{
	//VertexArray* Skybox::sSkyboxVertexArray = nullptr;

	// Identity box
	float SkyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};


	void Skybox::Bind(VertexArray* vertex_array, int slot)
	{
		vertex_array->Bind();
		mSkybox.Bind(slot);
	}


	glm::mat4 Skybox::GetViewMatrix(glm::mat4 view, float rotation)
	{
		view = glm::rotate(view, rotation, glm::vec3(0, 1, 0));
		view = glm::mat4(glm::mat3(view));
		return view;
	}


	//void Skybox::Init()
	//{
	//	sSkyboxVertexArray = new VertexArray();
	//	VertexBuffer vb = VertexBuffer(SkyboxVertices, sizeof(SkyboxVertices));
	//	
	//	BufferLayout layout{
	//		{GLSLDataType::Float3, "Position" }
	//	};
	//
	//	vb.SetLayout(layout);
	//	sSkyboxVertexArray->AddVertexBuffer(std::move(vb));
	//}

}

