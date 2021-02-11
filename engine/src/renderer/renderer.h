#pragma once

#include "core/timer.h"
#include "renderer_base.h"
#include "vertex_array.h"
#include "framebuffer.h"
#include "shader.h"
#include "model.h"
#include "skybox.h"
#include "buffer.h"
#include "uniform_buffer.h"
#include "camera.h"
#include "light.h"
#include "scene/scene.h"
#include "scene/components.h"

#include "glm/glm.hpp"
#include "glm-AABB/AABB.hpp"

#include "optimizations/frustum_culling .h"


namespace Bubble
{
    enum class DrawType { POINTS, LINES, TRIANGLES };

    struct Renderer
    {
        // Uniform buffer
        Scope<UniformBuffer> mUBOPrjectionview;
        Scope<UniformBuffer> mUBOLights;
        Scope<UniformBuffer> mUBOViewPos;

        // Scene components
        const Camera* mActiveCamera;
        const Framebuffer* mActiveViewport;
        glm::ivec2 mRenderPos;
        glm::ivec2 mRenderSize;

        Ref<Skybox> mSkyboxFirst;
        Ref<Skybox> mSkyboxSecond;
        Ref<Shader> mSkyboxShader;
        float mSkyboxBlendFactor;
        float mSkyboxBrightness;
        float mSkyboxRotation;
        float mSkyboxRotationSpeed;

        // Optimization
        std::vector<GLSL_Light> ActiveLights;


        void Init();

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

        // ============ Getters ============
        UniformBuffer& GetUBOPojectionView() { return *mUBOPrjectionview; }

        // ============ Clearing ============
        void SetClearColor(const glm::vec4& color);
        void Clear();
        void ClearDepth();
        void ClearColor();

        // ============ Rendering ============
        void DrawIndices(const Ref<VertexArray>& vertexArray, DrawType draw_type = DrawType::TRIANGLES, uint32_t count = 0);

        void DrawMesh(const Mesh& mesh, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);
        void DrawMesh(const Ref<Mesh>& mesh, const Ref<Shader>& shader, DrawType draw_type = DrawType::TRIANGLES);

        void DrawModel(const Ref<Model>& model, const glm::mat4& transforms, const Ref<Shader>& shader = nullptr, DrawType draw_type = DrawType::TRIANGLES);
        void DrawModelA(const Ref<Model>& model, const glm::mat4& transforms, const Ref<Shader>& shader = nullptr, DrawType draw_type = DrawType::TRIANGLES);

        void DrawSkybox(const Ref<Skybox>* skybox, int size, const Ref<Shader>& shader);

        void DrawScene(Scene& scene);

    private:
        void InitUBOS();
    };
}