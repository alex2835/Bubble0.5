
#include "resource_storage.h"

namespace Bubble
{
	RendererStorage::RendererStorage(Loader& loader)
	{
		// ============ Shaders ============
		mPhongShader  = loader.GetSystemShader("Phong shader");
		mSkyboxShader = loader.GetSystemShader("Skybox shader");
        mSkysphereShader = loader.GetSystemShader("Skysphere shader");

        // ======= Skybox vertex buffer =======
        BufferLayout layout{
            {GLSLDataType::Float3, "Position" }
        };
        mSkyboxVertexArray = CreateRef<VertexArray>();
        VertexBuffer vb = VertexBuffer(SkyboxVertices, sizeof(SkyboxVertices));
        vb.SetLayout(layout);
        mSkyboxVertexArray->AddVertexBuffer(std::move(vb));

        // =========== Sky sphere ===========
        mSphere = loader.GetSystemModel("sphere");
	}
} 