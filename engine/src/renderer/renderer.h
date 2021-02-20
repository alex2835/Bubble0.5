#pragma once

#include "glm/glm.hpp"
#include "glm-AABB/AABB.hpp"

#include "core/timer.h"
#include "scene/scene.h"
#include "scene/components.h"

#include "renderer_scene_state.h"
#include "renderer_storage/renderer_storage.h"
#include "rendering_optimizations/frustum_culling .h"

namespace Bubble
{
    enum class DrawType { POINTS = GL_POINT, LINES = GL_LINES, TRIANGLES = GL_TRIANGLES };
    enum class BackgroundType { COLOR, SKYBOX, SKYSPHERE };

    struct Renderer
    {
        // Uniform buffers
        Ref<UniformBuffer> mUBOProjectionView;
        Ref<UniformBuffer> mUBOViewPosition;
        Ref<UniformBuffer> mUBOLights;

        // Renderer stage
        const Camera*      mActiveCamera;
        const Framebuffer* mActiveViewport;
        glm::ivec2 mRenderingPos;
        glm::ivec2 mRenderingSize;

        // Internal usage data
        RendererStorage    mStorage;
        RendererSceneStage mSceneStage;

        // Rendering options
        BackgroundType mBackgroundType;
        //bool mClearScreanOption = false;
        //bool mWireframeOption   = false;
        //bool mBoundingBoxOption = false;


        Renderer(Loader* loader);
        // ============ Options ============
        void Wareframe(bool);
        void AlphaBlending(bool, uint32_t sfactor = GL_SRC_ALPHA, uint32_t dfactor = GL_ONE_MINUS_SRC_ALPHA);
        void BackfaceCulling(bool);
        void DepthTest(bool);

        // ============ Set active components ============
        void SetViewport(const Framebuffer& framebuffer, uint32_t x = 0, uint32_t y = 0, uint32_t width = 0, uint32_t height = 0);
        // Set viewport first
        void SetCamera(const Camera& camera);
        void SetLights(const std::vector<GLSL_Light>& lights);
        void SetLights(const GLSL_Light* lights, int size);

        // ============ Clearing ============
        void SetClearColor(const glm::vec4& color);
        void Clear();
        void ClearDepth();
        void ClearColor();

        // ============ Rendering ============
        void DrawIndices(const Ref<VertexArray>& vertexArray, DrawType draw_type = DrawType::TRIANGLES, uint32_t count = 0);

        void DrawMesh(const Mesh& mesh, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);
        void DrawMesh(const Ref<Mesh>& mesh, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);

        void DrawModel (const Ref<Model>& model, const glm::mat4& transforms, const Ref<Shader>& shader = nullptr, DrawType draw_type = DrawType::TRIANGLES);
        void DrawModelA(const Ref<Model>& model, const glm::mat4& transforms, const Ref<Shader>& shader = nullptr, DrawType draw_type = DrawType::TRIANGLES);

        void DrawSkybox(const Ref<Skybox>* skybox, int size, const Ref<Shader>& shader);
        void DrawSkysphere(const Ref<Texture2D>& skysphere_texture);

        void DrawScene(Scene& scene);

    private:
        void InitUBOS();
    };
}