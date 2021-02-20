
#include "renderer_storage.h"
#include "renderer_data.h"

namespace Bubble
{
	RendererStorage::RendererStorage(Loader* loader)
	{
		// ============ Shaders ============
		mPhongShader  = loader->LoadShader("Phong shader",  PhongVertexShaderSource,  PhongFragmentShaderSource);
		mSkyboxShader = loader->LoadShader("Skybox shader", SkyboxVertexShaderSource, SkyboxFragmentShaderSource);

        // ======= Skybox vertex buffer =======
        BufferLayout layout{
            {GLSLDataType::Float3, "Position" }
        };
        mSkyboxVertexArray = CreateRef<VertexArray>();
        VertexBuffer vb = VertexBuffer(SkyboxVertices, sizeof(SkyboxVertices));
        vb.SetLayout(layout);
        mSkyboxVertexArray->AddVertexBuffer(std::move(vb));

        // =========== Sky sphere ===========
        mSphere = loader->LoadModel("resources/models/sphere.obj");
        mSphere->mMeshes[0].mMaterial.mAmbientCoef = 2.0f;
        loader->mLoadedModels.clear();
	}

} 