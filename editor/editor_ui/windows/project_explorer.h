#pragma once

#include "ui_module.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace Bubble
{
	enum class DirItemType { Dir, Image, ModelDir };
	struct DirItem
	{
		std::string Path;
		DirItemType Type;
	};
	using DirNode = Tree<DirItem>::Node;
	using DirTree = Tree<DirItem>;


	struct ProjectExplorer : UIModule
	{
		Project* mProject = nullptr;
		DirTree  mDirTree;

		ProjectExplorer()
			: UIModule("Project explorer")
		{}

		inline void Draw(UIArgs args, DeltaTime dt)
		{
			DrawProjectTree();
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
				mDirTree.SetRoot(DirNode({ "C:/Users/sa007/Desktop"s, DirItemType::Dir }));
				IterateOverDirectory(mDirTree.GetRoot());
			}
		}

		void IterateOverDirectory(DirNode& root)
		{
			for (auto& dir_item : fs::directory_iterator(root.GetData().Path))
			{
				if (dir_item.is_directory())
				{
					DirNode dir = DirNode({ NormalizePath(dir_item.path()), DirItemType::Dir });
					IterateOverDirectory(dir);
					root.Append(std::move(dir));
				}
			}

		}

		void DrawProjectTree()
		{
			ImGui::Begin(mName.c_str(), &mIsOpen);
			{
				DrawDir(mDirTree.GetRoot());
			}
			ImGui::End();
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
						DrawDir(child);
						ImGui::TreePop();
					}
				}
			}
		}

	};

}