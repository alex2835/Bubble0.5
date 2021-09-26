#pragma once

#include "lib/tree.h"
#include "lib/str.h"
#include <string>
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
		DirItem(std::string path, DirItemType type)
			: Path(std::move(path)),
			  Type(type)
		{}

		std::string GetModelPath()
		{
			auto model_path = GetModelPathInDir(Path);
			BUBBLE_ASSERT(model_path, "Try get model path from dir where no models");
			return *model_path;
		}

		static std::optional<std::string> GetModelPathInDir(const std::string& path)
		{
			for (const auto& dir_item : fs::directory_iterator(path))
			{
				auto file_path = NormalizePath(dir_item.path());
				auto file_ext  = RightPartLastOf(file_path, ".");
				if (file_ext == "obj")
					return file_path;
			}
			return std::nullopt;
		}
	};
	using DirNode = Tree<DirItem>::Node;
	using DirTree = Tree<DirItem>;


	class Loader;

   class Project
   {
   public:
	   //Project() = default;
	   Project(Loader&);
	   ~Project();

      void Create(std::string dir_path, std::string name);
      void Open(std::string path);
      void Save(std::string path);

      bool Valid() const;
      std::string GetPath() const;
      std::string GetName() const;
      std::string GetPathWithName() const;

	  void UpdateProjectTree();
	  DirNode& GetProjectTreeRoot();

   private:
	   Loader& mLoader;
	   std::string mPath;
	   DirTree mProjectTree;

	   void IterateOverDirectoryAndFillTree(DirNode& root);
   };
}
