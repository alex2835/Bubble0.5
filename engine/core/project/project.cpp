
#include "project.h"

namespace Bubble
{
   void Project::Open(std::string path)
   {
      mPath = std::move(path);
   }

   void Project::Save(std::string path)
   {
      mPath = std::move(path);
   }

   bool Project::Valid()
   {
       return mPath.empty();
   }

   std::string Project::GetPath()
   {
      size_t pos = mPath.find_last_of("/") + 1;
      return mPath.substr(0, pos);
   }

   std::string Project::GetName()
   {
      size_t pos = mPath.find_last_of("/") + 1;
      return mPath.substr(pos);
   }

   std::string Project::GetPathWithName()
   {
      return mPath;
   }
}