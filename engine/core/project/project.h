#pragma once

#include <string>
#include <string_view>

namespace Bubble
{
   class Project
   {
   public:

      void Create(std::string dir_path, std::string name);
      void Open();
      void Save();

      std::string_view GetPath();
      std::string_view GetName();
      std::string_view GetPathWithName();

   private:
      std::string mPath;

   };
}
