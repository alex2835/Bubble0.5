#pragma once

#include "ui_module.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace Bubble
{
	enum class DirItemType { Dir, Image, ModelDir, Unnown };
	struct DirItem
	{
		std::string Path;
		DirItemType Type;

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
		Project* mProject = nullptr;
		DirTree  mDirTree;
		DirNode* mSelectedDir = nullptr;

		ProjectExplorer()
			: UIModule("Project explorer")
		{}

		inline void Draw(UIArgs args, DeltaTime dt)
		{
			mProject = args.mProject;

			ImGui::Begin(mName.c_str(), &mIsOpen);
			{
				ImGui::BeginChild("Project tree explorer", ImVec2(300, 300), false);
				DrawProjectTree();
				ImGui::EndChild();
			
				ImGui::SameLine();
				ImGui::BeginChild("Files in the directory", ImVec2(300, 300), false);
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
				//mDirTree.SetRoot(DirNode({ mProject->GetPath(), DirItemType::Dir }));
				mDirTree.SetRoot(DirNode("C:/Users/sa007/Desktop/", DirItemType::Dir));
				IterateOverDirectory(mDirTree.GetRoot());
			}
		}

		void IterateOverDirectory(DirNode& root)
		{
			for (auto& dir_item : fs::directory_iterator(root.GetData().Path))
			{
				if (dir_item.is_directory())
				{
					DirNode dir = DirNode(NormalizePath(dir_item.path()), DirItemType::Dir);
					IterateOverDirectory(dir);
					root.Append(std::move(dir));
				}
				else
					root.Append(NormalizePath(dir_item.path()), DirItemType::Unnown);
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
					auto dir_name = child.GetData().Path;
					dir_name = dir_name.substr(dir_name.find_last_of("/") + 1);

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
			if (mSelectedDir)
			{
				for (DirItem& item : *mSelectedDir)
				{
					auto dir_name = item.Path;
					dir_name = dir_name.substr(dir_name.find_last_of("/") + 1);

					if (item.Type != DirItemType::Dir)
						ImGui::BulletText(dir_name.c_str());
				}
			}
		}

	};

}