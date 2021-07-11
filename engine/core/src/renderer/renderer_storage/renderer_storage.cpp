
#include "renderer_storage.h"
#include "renderer_data.h"

namespace Bubble
{
	RendererStorage::RendererStorage(Loader& loader)
	{
        using namespace std::string_literals;

		// ============ Shaders ============
		mPhongShader  = loader.LoadShader("Phong shader"s,  PhongVertexShaderSource,  PhongFragmentShaderSource);
		mSkyboxShader = loader.LoadShader("Skybox shader"s, SkyboxVertexShaderSource, SkyboxFragmentShaderSource);
        mSkysphereShader = loader.LoadShader("Skysphere shader"s, SkysphereVertexShaderSource, SkysphereFragmentShaderSource);

        // ======= Skybox vertex buffer =======
        BufferLayout layout{
            {GLSLDataType::Float3, "Position" }
        };
        mSkyboxVertexArray = CreateRef<VertexArray>();
        VertexBuffer vb = VertexBuffer(SkyboxVertices, sizeof(SkyboxVertices));
        vb.SetLayout(layout);
        mSkyboxVertexArray->AddVertexBuffer(std::move(vb));

        // =========== Sky sphere ===========
        mSphere = loader.LoadModel("resources/models/sphere.obj");
	}
    
} 