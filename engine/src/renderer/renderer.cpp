
#include "renderer.h"


namespace Bubble
{
    Scope<UniformBuffer> Renderer::sUBOLights;
    Scope<UniformBuffer> Renderer::sUBOPrjectionview;
    Scope<UniformBuffer> Renderer::sUBOViewPos;

    // Scene components
    const Camera* Renderer::sActiveCamera;
    const Framebuffer* Renderer::sActiveViewport;
    glm::ivec2 Renderer::sRenderPos;
    glm::ivec2 Renderer::sRenderSize;

    Ref<Skybox> Renderer::sSkyboxFirst;
    Ref<Skybox> Renderer::sSkyboxSecond;
    Ref<Shader> Renderer::sSkyboxShader;
    float Renderer::sSkyboxBrightness;
    float Renderer::sSkyboxBlendFactor;
    float Renderer::sSkyboxRotation;
    float Renderer::sSkyboxRotationSpeed;

    // Optimizations
    std::vector<GLSL_Light> Renderer::ActiveLights;


    static uint32_t OpenGLDrawType(DrawType draw_type)
    {
        uint32_t opengl_draw_type = 0;
        switch (draw_type)
        {
        case DrawType::POINTS:
            opengl_draw_type = GL_POINT;
            break;
        case DrawType::LINES:
            opengl_draw_type = GL_LINES;
            break;
        case DrawType::TRIANGLES:
            opengl_draw_type = GL_TRIANGLES;
            break;
        default:
            BUBBLE_CORE_ASSERT(false, "Unknown draw type");
        }
        return opengl_draw_type;
    }


    void Renderer::Init()
    {
        InitUBOS();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        sSkyboxShader = Loader::LoadShader("resources/shaders/skybox.glsl");
    }

    // =================== Options ===================

    void Renderer::Wareframe(bool on)
    {
        if (on) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void Renderer::AlphaBlending(bool on, uint32_t sfactor, uint32_t dfactor)
    {
        if (on) {
            glEnable(GL_BLEND);
            glBlendFunc(sfactor, dfactor);
        }
        else {
            glDisable(GL_BLEND);
        }
    }

    void Renderer::BackfaceCulling(bool on)
    {
        on ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    }

    void Renderer::DepthTest(bool on)
    {
        on ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }


    // =================== Set active components ===================

    void Renderer::SetCamera(const Camera& camera)
    {
        BUBBLE_CORE_ASSERT(sActiveViewport, "Set viewport first");
        sActiveCamera = &camera;

        glm::ivec2 window_size = sRenderSize - sRenderPos;
        glm::mat4 projection = camera.GetPprojectionMat(window_size.x, window_size.y);
        glm::mat4 view = camera.GetLookatMat();

        // Set projection-view Uniform Buffer
        glm::mat4 projection_view[2] = { projection, view };
        sUBOPrjectionview->SetData(projection_view, sizeof(projection_view));

        // Set camera frustum
        SetFrustumPlanes(projection * view);

        // Set camera position
        (*sUBOViewPos)[0].SetFloat3("ViewPos", camera.Position);
    }


    void Renderer::SetLights(const std::vector<GLSL_Light>& lights)
    {
        int offset = 16;
        int nLights = lights.size();

        sUBOLights->SetData(&nLights, 4);
        sUBOLights->SetData(lights.data(), sizeof(GLSL_Light) * nLights, offset);
    }

    void Renderer::SetLights(const GLSL_Light* lights, int size)
    {
        int offset = 16;
        sUBOLights->SetData(lights, sizeof(GLSL_Light) * size, offset);
        sUBOLights->SetData(&size, 4);
    }

    void Renderer::SetViewport(const Framebuffer& framebuffer, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        if (width * height) {
            sRenderPos = { x, y };
            sRenderSize = { width, height };
        }
        else {
            sRenderPos = { 0, 0 };
            sRenderSize = { framebuffer.GetWidth(), framebuffer.GetHeight() };
        }
        framebuffer.Bind();
        sActiveViewport = &framebuffer;
        glViewport(sRenderPos.x, sRenderPos.y, sRenderSize.x, sRenderSize.y);
    }


    // ======================== Clearing ========================

    void Renderer::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ClearDepth()
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ClearColor()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }


    // ==================== Rendering ====================

    void Renderer::DrawIndices(const Ref<VertexArray>& vertex_array, DrawType draw_type, uint32_t index_count)
    {
        vertex_array->Bind();
        uint32_t count = index_count ? index_count : vertex_array->GetIndexBuffer().GetCount();
        glcall(glDrawElements(OpenGLDrawType(draw_type), count, GL_UNSIGNED_INT, nullptr));
    }


    void Renderer::DrawMesh(const Ref<Mesh>& mesh, const Ref<Shader>& shader, DrawType draw_type)
    {
        Renderer::DrawMesh(*mesh.get(), shader, draw_type);
    }


    void Renderer::DrawMesh(const Mesh& mesh, const Ref<Shader>& shader, DrawType draw_type)
    {
        mesh.mVertexArray.Bind();
        mesh.mMaterial.Set(shader);
        glDrawElements(OpenGLDrawType(draw_type), mesh.mIndices.size(), GL_UNSIGNED_INT, 0);
    }


    void Renderer::DrawModel(const Ref<Model>& model, const glm::mat4& transforms, const Ref<Shader>& in_shader, DrawType draw_type)
    {
        const Ref<Shader>& shader = in_shader ? in_shader : model->mShader;

        if (IsInFrustum(model->mBoundingBox.transform(transforms)))
        {
            shader->SetUniMat4("u_Model", transforms);
            for (const auto& mesh : model->mMeshes)
            {
                Renderer::DrawMesh(mesh, shader, draw_type);
            }
        }
    }


    void Renderer::DrawModelA(const Ref<Model>& model, const glm::mat4& transforms, const Ref<Shader>& in_shader, DrawType draw_type)
    {
        AlphaBlending(true);
        Renderer::DrawModel(model, transforms, in_shader, draw_type);
        AlphaBlending(false);
    }


    void Renderer::DrawSkybox(const Ref<Skybox>* skybox, int size, const Ref<Shader>& shader)
    {
        shader->Bind();
        for (int i = 0; i < size; i++)
        {
            shader->SetUni1i("u_Skybox" + std::to_string(i), i);
            skybox[i]->Bind(i);
        }
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
    }


    void Renderer::DrawScene(Scene& scene)
    {
        auto scene_view = scene.GetView<ModelComponent, TransformComponent>();

        // Temp: Extract all lights
        ActiveLights.clear();
        scene.Registry.view<LightComponent>().each(
            [&](auto& entity, LightComponent& light)
            {
                light.Update();
                ActiveLights.push_back(light);
            }
        );
        SetLights(ActiveLights);

        // Draw scene
        for (auto entity : scene_view)
        {
            auto [model, transforms] = scene_view.get<ModelComponent, TransformComponent>(entity);
            if (IsInFrustum(model->mBoundingBox.transform(transforms)))
            {
                Renderer::DrawModel(model, transforms);
            }
        }

        // Draw skybox
        glm::mat4 view = sActiveCamera->GetLookatMat();
        sSkyboxRotation += Timer::GetTime().GetSeconds() * sSkyboxRotationSpeed * 0.00002f;
        view = Skybox::GetViewMatrix(view, sSkyboxRotation);
        Renderer::GetUBOPojectionView()[0].SetMat4("View", view);

        sSkyboxShader->SetUni1f("u_Brightness",  sSkyboxBrightness);
        sSkyboxShader->SetUni1f("u_BlendFactor", sSkyboxBlendFactor);

        Ref<Skybox> skyboxes[] = { sSkyboxFirst, sSkyboxSecond };
        Renderer::DrawSkybox(skyboxes, 2, sSkyboxShader);
    }


    // ======================== UBO ======================== 

    void Renderer::InitUBOS()
    {
        // Init Projection View UBO
        BufferLayout UBOProjectionViewLayout{
            { GLSLDataType::Mat4, "Projection" },
            { GLSLDataType::Mat4, "View" }
        };
        sUBOPrjectionview = CreateScope<UniformBuffer>(0, UBOProjectionViewLayout);

        // Init Lights UBO
        BufferLayout layout{
            { GLSLDataType::Int,    "Type"},
            { GLSLDataType::Float,  "Brightness"},
            { GLSLDataType::Float,  "Constant"},
            { GLSLDataType::Float,  "Linear"},
            { GLSLDataType::Float,  "Quadratic"},
            { GLSLDataType::Float,  "CutOff"},
            { GLSLDataType::Float,  "OuterCutOff"},
            { GLSLDataType::Float3, "Color"},
            { GLSLDataType::Float3, "Direction"},
            { GLSLDataType::Float3, "Position"},
        };
        int nLights = 30;
        int reserved_data = 16; // for nLights
        sUBOLights = CreateScope<UniformBuffer>(1, layout, nLights, reserved_data);

        // Init view position UBO
        BufferLayout UBOViewPosLayout{
            { GLSLDataType::Float3, "ViewPos" },
        };
        sUBOViewPos = CreateScope<UniformBuffer>(2, UBOViewPosLayout);
    }

}