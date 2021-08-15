#pragma once

#include <string>
#include <string_view>

namespace Bubble
{
   class Project
   {
   public:

      void Create(std::string dir_path, std::string name);
      void Open(std::string path);
      void Save(std::string path);

      bool Valid();;
      std::string GetPath();
      std::string GetName();
      std::string GetPathWithName();

   private:
      std::string mPath;

   };
}
