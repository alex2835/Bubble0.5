
#include "loader.h"
#include "project/project.h"

#include "default_resources.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace Bubble
{
   Loader::Loader(Project& prj)
      : mProject(prj)
   {
       LoadSystemShader("Phong shader", PhongVertexShaderSource, PhongFragmentShaderSource);
       LoadSystemShader("Skybox shader", SkyboxVertexShaderSource, SkyboxFragmentShaderSource);
       LoadSystemShader("Skysphere shader", SkysphereVertexShaderSource, SkysphereFragmentShaderSource);

       LoadSystemTexture("resources/textures/chess_plane.jpg");

       // icons
       LoadSystemTexture("resources/textures/dir_icon.jpg");
       LoadSystemTexture("resources/textures/texture_icon.jpg");
       LoadSystemTexture("resources/textures/model_icon.jpg");
       LoadSystemTexture("resources/textures/file_icon.jpg");

       // models
       LoadSystemModel("resources/models/sphere/sphere.obj");
   }

   void Loader::LoadProjectResources()
   {
       LoadItemsFromDir(mProject.GetProjectTreeRoot());
   }

   void Loader::LoadItemsFromDir(DirNode& dir)
   {
	   for (auto& child : dir)
	   {
           auto& item = child.GetData();
           switch (item.Type)
           {
		       case DirItemType::Dir:
                   LoadItemsFromDir(child);
			       break;
		       case DirItemType::Texture:
                   LoadAndCacheTexture2D(item.Path);
			       break;
		       case DirItemType::ModelDir:
                   LoadAndCacheModel(item.GetModelPath());
			       break;
		       case DirItemType::Unnown:
		       default:
			       break;
           }
	   }
   }

}
