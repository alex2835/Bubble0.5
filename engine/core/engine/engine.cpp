
#include "engine.h"
namespace Bubble
{
   Engine::Engine()
      : mInput(mWindow),
        mLoader(mProject),
        mRenderer(mLoader)
   {}

   void Engine::OnEvent(SDL_Event& event)
   {
      mInput.OnEvent(event);
      mWindow.OnEvent(event);
   }

   void Engine::OnUpdate()
   {
      mWindow.OnUpdate();
   }

}