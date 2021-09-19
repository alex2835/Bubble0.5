#pragma once

#include "ui_module.h"
#include "tools/imgui_widgets.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace Bubble
{
	enum class DirItemType { Dir, Texture, ModelDir, Unnown };
	struct DirItem
	{
		std::string Path;
		DirItemType Type = DirItemType::Unnown;

		DirItem() = default;
		DirItem(std::string path,
				DirItemType type)
			: Path(std::move(path)),
			  Type(type)
		{}
	};
	using DirNode = Tree<DirItem>::Node;
	using DirTree = Tree<DirItem>;


	struct ProjectExplorer : UIModule
	{
		DirTree  mDirTree;
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
			UpdateProjectFileTree();
		}

	private:
		void UpdateProjectFileTree()
		{
			static int i = 0;
			if (i++ == 0)
			{
				mDirTree.SetRoot(DirNode(mProject->GetPath(), DirItemType::Dir));
				//mDirTree.SetRoot(DirNode("C:/Users/sa007/Desktop/", DirItemType::Dir));
				IterateOverDirectoryAndFillTree(mDirTree.GetRoot());
				mSelectedDir = &mDirTree.GetRoot();
			}
		}

		void IterateOverDirectoryAndFillTree(DirNode& root)
		{
			for (const auto& dir_item : fs::directory_iterator(root.GetData().Path))
			{
				auto norm_path = NormalizePath(dir_item.path());
				auto file_ext  = RightPartLastOf(norm_path, ".");

				if (dir_item.is_directory())
				{
					if (IsModelDir(norm_path))
						root.Append(norm_path, DirItemType::ModelDir);
					else
					{
						DirNode dir = DirNode(norm_path, DirItemType::Dir);
						IterateOverDirectoryAndFillTree(dir);
						root.Append(std::move(dir));
					}
				}
				else if(file_ext == "png"s || file_ext == "jpg"s)
					root.Append(norm_path, DirItemType::Texture);
				else
					root.Append(norm_path, DirItemType::Unnown);
			}
		}

		// ============================ Draw ============================

		void DrawProjectTree()
		{
			DrawDir(mDirTree.GetRoot());
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

		bool IsModelDir(const std::string& path)
		{
			for (const auto& dir_item : fs::directory_iterator(path))
			{
				auto file_ext = RightPartLastOf(NormalizePath(dir_item.path()), ".");
				if (file_ext == "obj")
					return true;
			}
			return false;
		}

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