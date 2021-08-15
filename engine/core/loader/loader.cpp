#include "loader.h"
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

       LoadSystemModel("resources/models/sphere.obj");
   }

   std::string Loader::CopyToProject(std::string file_path, std::string type)
   {
       std::string type_dir = std::string(mProject.GetPath()) + type;
       if (!std::filesystem::exists(type_dir))
           fs::create_directory(type_dir);

       size_t start_pos = file_path.find_last_of("/") + 1;
       std::string name = file_path.substr(start_pos, file_path.size() - start_pos);
       return type + "/" + name;
   }


}
