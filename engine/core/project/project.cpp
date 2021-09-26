
#include "project.h"

namespace Bubble
{
	Project::Project(Loader& loader)
		: mLoader(loader)
	{}

	Project::~Project()
	{
	}

	void Project::Create(std::string dir_path, std::string name)
	{
		UpdateProjectTree();
		BUBBLE_ASSERT(false, "sadfasdf");
	}

   void Project::Open(std::string path)
   {
		mPath = std::move(path);
		UpdateProjectTree();
		mLoader.LoadProjectResources();
   }

   void Project::Save(std::string path)
   {
      mPath = std::move(path);
   }

   bool Project::Valid() const
   {
       return !mPath.empty();
   }

   std::string Project::GetPath() const
   {
      size_t pos = mPath.find_last_of("/") + 1;
      return mPath.substr(0, pos);
   }

   std::string Project::GetName() const
   {
      size_t pos = mPath.find_last_of("/") + 1;
      return mPath.substr(pos);
   }

   std::string Project::GetPathWithName() const
   {
      return mPath;
   }

   Bubble::DirNode& Project::GetProjectTreeRoot()
   {
	   return mProjectTree.GetRoot();
   }

   void Project::UpdateProjectTree()
   {
		mProjectTree.SetRoot(DirNode(GetPath(), DirItemType::Dir));
		IterateOverDirectoryAndFillTree(GetProjectTreeRoot());
   }

   void Project::IterateOverDirectoryAndFillTree(DirNode& root)
   {
	   for (const auto& dir_item : fs::directory_iterator(root.GetData().Path))
	   {
		   auto norm_path = NormalizePath(dir_item.path());
		   auto file_ext = RightPartLastOf(norm_path, ".");

		   if (dir_item.is_directory())
		   {
			   if (DirItem::GetModelPathInDir(norm_path))
				   root.Append(norm_path, DirItemType::ModelDir);
			   else
			   {
				   DirNode dir = DirNode(norm_path, DirItemType::Dir);
				   IterateOverDirectoryAndFillTree(dir);
				   root.Append(std::move(dir));
			   }
		   }
		   else if (file_ext == "png"s || file_ext == "jpg"s)
			   root.Append(norm_path, DirItemType::Texture);
		   else
			   root.Append(norm_path, DirItemType::Unnown);
	   }
   }

}