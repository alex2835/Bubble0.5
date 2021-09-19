#pragma once

#include "bubble.h"
#include "tools/file_dialog.h"
#include "ui_module.h"
#include <algorithm>

namespace Bubble
{
	struct ModelExplorer : UIModule
    {
        ThirdPersonCamera mCamera;
		Ref<Model>        mSelectedModel;
		Viewport          mViewport;
		Light             mLight;
        glm::mat4         mTransforms;
	 
        inline ModelExplorer()
            : UIModule("Model explorer"),
              mSelectedModel(nullptr),
              mViewport(800, 600),
			  mCamera(0),
              mTransforms(glm::mat4(1.0f))
        {
            mLight  = Light::CreateDirLight();
        }
		
		inline void Draw(UIArgs args, DeltaTime dt)
		{
            ImGui::Begin("Models explorer", &mIsOpen);
            {
                ImVec2 window_size = ImGui::GetContentRegionAvail();

                DrawViewport(window_size, args, dt);
                DrawSelectedModelInfo(window_size, args, dt);
                DrawModelsList(window_size, args, dt);
            }
            ImGui::End();
		}

        void OnUpdate(UIArgs args, DeltaTime dt) override
        {
            mViewport.OnUpdate();
        }

	private:

        // ======================= Viewport ======================= 
        inline void DrawViewport(ImVec2 window_size, UIArgs args, DeltaTime dt)
        {
            uint32_t texture_id   = mViewport.GetColorAttachmentRendererID();
            ImVec2 viewport_size = ImVec2(window_size.x * 0.7f, window_size.y * 0.75f);

            ImGui::Image((void*)texture_id, viewport_size, ImVec2(1, 1), ImVec2(0, 0));
            mViewport.mNewSize = *(glm::vec2*)&viewport_size;

            if (ImGui::IsItemVisible() && mSelectedModel)
                RenderSelectedModel(args.mRenderer);

            if (ImGui::IsWindowFocused())
            {
                // Rotate camera
                if (ImGui::IsMouseDragging(0))
                {
                    mCamera.ProcessMouseMovementShift(args.mInput->fGetMouseRelX(), -args.mInput->fGetMouseRelY());
                    mCamera.Update(dt);
                }
                // Rotate model
                if (ImGui::IsWindowFocused() && ImGui::IsMouseDragging(1))
                {
                    if (args.mInput->IsKeyPressed(SDLK_LSHIFT))
                        mTransforms = glm::rotate(mTransforms, 5 * args.mInput->fGetMouseRelX(), glm::vec3(1, 0, 0));
                    else if (args.mInput->IsKeyPressed(SDLK_LCTRL))
                        mTransforms = glm::rotate(mTransforms, 5 * args.mInput->fGetMouseRelX(), glm::vec3(0, 0, 1));
                    else
                        mTransforms = glm::rotate(mTransforms, 5 * args.mInput->fGetMouseRelX(), glm::vec3(0, 1, 0));
                }
            }

            // Change camera radius by mouse wheel scrolling
            if (ImGui::IsWindowHovered())
            {
                if (mSelectedModel)
                {
                    float longest_edge = mSelectedModel->mBoundingBox.getLongestEdge();
                    mCamera.Radius -= args.mInput->GetMouseWheelOffset() * longest_edge / 5;
                    mCamera.Radius  = glm::clamp(mCamera.Radius, longest_edge, mCamera.Far);
                    mCamera.Update(dt);
                }
            }
        }

        // ======================= Model info ======================= 
        inline void DrawSelectedModelInfo(ImVec2 window_size, UIArgs args, DeltaTime dt)
        {
            ImGui::SameLine();
            ImGui::BeginChild("Model info", ImVec2(0, window_size.y), false, ImGuiWindowFlags_HorizontalScrollbar);
            {
                if (mSelectedModel)
                {
                    DrawModelInfo(mSelectedModel);
                    DrawModelTree(mSelectedModel->mRootNode, args);
                }
            }
            ImGui::EndChild();
        }

        inline void DrawModelInfo(Ref<Model>& model)
        {
            int vertices = 0;
            int triangles = 0;
            for (auto& mesh : mSelectedModel->mMeshes)
            {
                vertices += mesh.mVertices.mPositions.size();
                triangles += mesh.mIndices.size() / 3;
            }
            ImGui::Text("Model info:");
            ImGui::Text("Vertices: %d", vertices);
            ImGui::Text("Triangles: %d", triangles);

            bool  change = false;
            float ambient_coef   = model->mMeshes[0].mMaterial.mAmbientCoef;
            float specular_coef  = model->mMeshes[0].mMaterial.mSpecularCoef;
            int   shininess_coef = model->mMeshes[0].mMaterial.mShininess;
            glm::vec4 diffuse_color   = model->mMeshes[0].mMaterial.mDiffuseColor;
            float normal_mapping_coef = model->mMeshes[0].mMaterial.mNormalMapStrength;

            change |= ImGui::ColorEdit4("Diffuse color", (float*)&diffuse_color);
            change |= ImGui::SliderFloat("Ambient",  &ambient_coef, 0.0f, 10.0f);
            change |= ImGui::SliderFloat("Specular", &specular_coef, 0.0f, 10.0f);
            change |= ImGui::SliderInt("Shininess",  &shininess_coef, 4, 1000);
            change |= ImGui::SliderFloat("NormalM strength", &normal_mapping_coef, 0.0f, 10.0f);

            if (change)
            {
                for (auto& mesh : model->mMeshes)
                {
                    mesh.mMaterial.mAmbientCoef  = ambient_coef;
                    mesh.mMaterial.mSpecularCoef = specular_coef;
                    mesh.mMaterial.mDiffuseColor = diffuse_color;
                    mesh.mMaterial.mShininess    = shininess_coef;
                    mesh.mMaterial.mNormalMapStrength = normal_mapping_coef;
                }
            }
            ImGui::Separator();
        }


        inline void DrawModelTree(Scope<MeshNode>& current_node, UIArgs args)
        {
            if (ImGui::TreeNode((int*)current_node.get() + (int)current_node->mName.data(), current_node->mName.c_str()))
            {
                for (auto mesh : current_node->mMeshes)
                    DrawMeshInfo(*mesh, args);

                for (auto& child : current_node->mChildern)
                    DrawModelTree(child, args);

                ImGui::TreePop();
            }
        }

        inline void DrawMeshInfo(Mesh& mesh, UIArgs args)
        {
            if (ImGui::TreeNode(mesh.mName.c_str(), mesh.mName.c_str()))
            {
                ImGui::Text("Vertices:  %d", mesh.mVertices.mPositions.size());
                ImGui::Text("Triangles: %d", mesh.mIndices.size() / 3);

                ImGui::ColorEdit4("Diffuse color", (float*)&mesh.mMaterial.mDiffuseColor);
                ImGui::SliderFloat("Ambient", &mesh.mMaterial.mAmbientCoef, 0.0f, 10.0f);
                ImGui::SliderFloat("Specular", &mesh.mMaterial.mSpecularCoef, 0.0f, 10.0f);
                ImGui::SliderInt("Shininess", &mesh.mMaterial.mShininess, 4, 256);
                ImGui::SliderFloat("NormalM strength", &mesh.mMaterial.mNormalMapStrength, 0.0f, 10.0f);

                ImVec2 image_size(100, 100);
                ImGui::Text("Diffuse "); ImGui::SameLine();
                ImGui::Image((ImTextureID)mesh.mMaterial.mDiffuseMap->mRendererID, image_size);
                if (ImGui::IsItemClicked())
                {
                    try {
                        std::string path = OpenFileDialog("png,jpg,tga");
                        mesh.mMaterial.mDiffuseMap = args.mLoader->LoadTexture2D(path);
                    }
                    catch (const std::exception& e)
                    {
                        LOG_ERROR("Diffuse map can't be opened");
                    }
                }

                ImGui::Text("Specular"); ImGui::SameLine();
                ImGui::Image((ImTextureID)mesh.mMaterial.mSpecularMap->mRendererID, image_size);
                if (ImGui::IsItemClicked())
                {
                    try {
                        std::string path = OpenFileDialog("png,jpg,tga");
                        mesh.mMaterial.mSpecularMap = args.mLoader->LoadTexture2D(path);
                    }
                    catch (const std::exception& e)
                    {
                        LOG_ERROR("Specular map can't be opened");
                    }
                }

                ImGui::Text("Normal  "); ImGui::SameLine();
                if (mesh.mMaterial.mNormalMap)
                {
                    ImGui::Image((ImTextureID)mesh.mMaterial.mNormalMap->mRendererID, image_size);
                }
                else {
                    //const auto& chess_plane = args.mLoader->LoadTexture2D("resources/images/chess_plane.jpg");
                    const auto& chess_plane = args.mLoader->GetSystemTexture("chess_plane");
                    ImGui::Image((ImTextureID)chess_plane->GetRendererID(), image_size);
                }

                if (ImGui::IsItemClicked())
                {
                    try {
                        std::string path = OpenFileDialog("png,jpg,tga");
                        mesh.mMaterial.mNormalMap = args.mLoader->LoadTexture2D(path);
                    }
                    catch (const std::exception& e)
                    {
                        LOG_ERROR("Normal map can't be opened");
                    }
                }
                ImGui::TreePop();
                ImGui::Separator();
            }
        }


        // ======================= Model list ======================= 
        inline void DrawModelsList(ImVec2 window_size, UIArgs args, DeltaTime dt)
        {
            ImGui::SetCursorPos(ImVec2(8, window_size.y * 0.75f + 31));

            ImGui::BeginChild("Models list", ImVec2(window_size.x * 0.5f, window_size.y * 0.24f), true);
            {
                for (const auto& [path, model] : args.mLoader->mLoadedModels)
                {
                    size_t pos  = path.find_last_of("/") + 1;
                    size_t dpos = path.find_last_of(".");
                    std::string name = path.substr(pos, dpos - pos);

                    ImGui::Selectable(name.c_str(), mSelectedModel == model);

                    // Switch 
                    if (ImGui::IsItemClicked())
                    {
                        mSelectedModel = model;
                        mTransforms = glm::mat4(1.0f);
                        // Start camera params for this model
                        mCamera.Center = mSelectedModel->mBoundingBox.getCenter();
                        mCamera.Radius = mSelectedModel->mBoundingBox.getLongestEdge() * 1.5f;
                        mCamera.Update(dt);
                    }
                }

                if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                {
                    mSelectedModel = nullptr;
                }
            }
            ImGui::EndChild();


            // Buttons
            ImGui::SameLine();
            ImGui::BeginChild("Buttons", ImVec2(window_size.x * 0.2f - 7, window_size.y * 0.24f), true);
            {
                if (ImGui::Button("Load", ImVec2(window_size.x * 0.2f - 23, window_size.y * 0.05f)))
                {
                    try
                    {
                        std::string path = OpenFileDialog();
                        args.mLoader->LoadAndCacheModel(path);
                    }
                    catch (const std::exception& e)
                    {
                        LOG_ERROR(e.what());
                    }
                }
                if (ImGui::Button("Delete", ImVec2(window_size.x * 0.2f - 23, window_size.y * 0.05f)))
                {
                    if (mSelectedModel)
                    {
                        auto begin = args.mLoader->mLoadedModels.begin();
                        auto end   = args.mLoader->mLoadedModels.end();
                        auto selected_model = std::find_if(begin, end,
                            [this](const auto& pair) { return pair.second == mSelectedModel; });
                        args.mLoader->mLoadedModels.erase(selected_model);
                        mSelectedModel = nullptr;
                    }
                }
            }
            ImGui::EndChild();

        }

        inline void RenderSelectedModel(Renderer* renderer)
        {
            renderer->SetViewport(mViewport);
            renderer->SetCamera(mCamera);
            renderer->SetLights(&mLight, 1);

            renderer->SetClearColor(glm::vec4(0.4f));
            renderer->Clear();

            renderer->DrawModel(mSelectedModel, mTransforms, renderer->mStorage.mPhongShader);
        }
    };

}