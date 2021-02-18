
#include "renderer_storage.h"
#include "renderer_data.h"

namespace Bubble
{
	RendererStorage::RendererStorage(Loader* loader)
	{
		// ======= Skybox vertex buffer =======
		BufferLayout layout{
			{GLSLDataType::Float3, "Position" }
		};
		mSkyboxVertexArray = CreateRef<VertexArray>();
		VertexBuffer vb = VertexBuffer(SkyboxVertices, sizeof(SkyboxVertices));
		vb.SetLayout(layout);
		mSkyboxVertexArray->AddVertexBuffer(std::move(vb));

		// ============ Shaders ============
		mPhongShader  = loader->LoadShader("Phong shader",  PhongVertexShaderSource,  PhongFragmentShaderSource);
		mSkyboxShader = loader->LoadShader("Skybox shader", SkyboxVertexShaderSource, SkyboxFragmentShaderSource);
	}

} 