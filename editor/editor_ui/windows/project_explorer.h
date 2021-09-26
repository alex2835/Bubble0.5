#pragma once

#include "ui_module.h"
#include "tools/imgui_widgets.h"

namespace Bubble
{
	struct ProjectExplorer : UIModule
	{
		DirNode* mSelectedDir = nullptr;
		Project* mProject = nullptr;
		Loader*  mLoader  = nullptr;

		ProjectExplorer()
			: UIModule("Project explorer")
		{}

		inline void Draw(UIArgs args, DeltaTime dt)
		{
			mProject = args.mProject;
			mLoader  = args.mLoader;

			ImGui::Begin(mName.c_str(), &mIsOpen);
			{
				ImGui::BeginChild("Project tree explorer", ImVec2(250, 0), false);

				if (ImGui::Button("Update", ImVec2(50, 20)))
					mProject->UpdateProjectTree();

				DrawProjectTree();
				ImGui::EndChild();
			
				ImGui::SameLine();
				ImGui::BeginChild("Files in the directory");
				DrawItemsInSelectedDir();
				ImGui::EndChild();
			}
			ImGui::End();
		}

		void OnUpdate(UIArgs args, DeltaTime dt) override
		{
		}

	private:

		// ============================ Draw ============================
		
		void DrawProjectTree()
		{
			DrawDir(mProject->GetProjectTreeRoot());
		}

		void DrawDir(DirNode& root)
		{
			for (auto& child : root)
			{
				if (child.GetData().Type == DirItemType::Dir)
				{
					auto dir_name = RightPartLastOf(child.GetData().Path, "/");

					if (ImGui::TreeNode(dir_name.c_str(), dir_name.c_str()))
					{
						if (ImGui::IsItemToggledOpen() || ImGui::IsItemClicked())
							mSelectedDir = &child;

						DrawDir(child);
						ImGui::TreePop();
					}
				}
			}
		}

		void DrawItemsInSelectedDir()
		{
			if (!mSelectedDir)
				return;

			int i = 0;
			for (DirItem& item : *mSelectedDir)
				DrawDirItem(item, i++);
		}

		void DrawDirItem(const DirItem& item, int pos)
		{
			auto item_name = RightPartLastOf(item.Path, "/");
			ImVec2 window_size = ImGui::GetWindowSize();
			auto elem_length = window_size.x / 5.5f;
			ImVec2 elem_size = ImVec2(elem_length, elem_length);
			DrawImageWithText(GetTextureByItemType(item), RightPartLastOf(item.Path, "/"), elem_size, 5, pos);
		}

		// ========================== details ==========================

		Ref<Texture2D> GetTextureByItemType(const DirItem& item)
		{
			Ref<Texture2D> texture;
			switch (item.Type)
			{
				case DirItemType::Dir:
					return mLoader->GetSystemTexture("dir_icon");
					break;
				case DirItemType::Texture:
					return mLoader->GetSystemTexture("texture_icon");
					break;
				case DirItemType::ModelDir:
					return mLoader->GetSystemTexture("model_icon");
					break;
				case DirItemType::Unnown:
					return mLoader->GetSystemTexture("file_icon");
					break;
				default:
					return mLoader->GetSystemTexture("chess_plane");
			}
		}

	};

}