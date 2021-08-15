#pragma once

// Engine core
#include "../core/base/base.h"
#include "../core/base/log.h"
#include "../core/base/timer.h"

#include "../core/application/layer.h"
#include "../core/application/layer_array.h"
#include "../core/application/window.h"
#include "../core/application/input.h"

// Renderer
#include "../core/renderer/core/renderer_base.h"
#include "../core/renderer/core/framebuffer.h"
#include "../core/renderer/core/buffer.h"
#include "../core/renderer/core/uniform_buffer.h"
#include "../core/renderer/core/vertex_array.h"
#include "../core/renderer/core/shader.h"
#include "../core/renderer/core/texture.h"
#include "../core/renderer/core/cubemap.h"
#include "../core/renderer/core/skybox.h"
#include "../core/renderer/core/camera.h"
#include "../core/renderer/core/camera_free.h"
#include "../core/renderer/core/camera_target.h"
#include "../core/renderer/core/camera_third_person.h"
#include "../core/renderer/renderer.h"
//#include "../core/renderer/renderer_serialization.h"

// Scene
#include "../core/scene/scene.h"
#include "../core/scene/entity.h"
#include "../core/scene/components.h"
//#include "../core/scene/entity_serialization.h"

// Loader
#include "../core/loader/loader.h"
//#include "../core/loader/loader_serialization.h"


namespace Bubble
{
   class Engine
   {
   public:
      Engine();

      void OnEvent(SDL_Event& event);
      void OnUpdate();

      Window&   GetWindow(){ return mWindow; };
      Loader&   GetLoader(){ return mLoader; };
      Renderer& GetRenderer(){ return mRenderer; };
      Input&    GetInput(){ return mInput; };
      Scene&    GetScene(){ return mScene; };
      Project&  GetProject(){ return mProject; };
   private:
       Window   mWindow;
       Project  mProject;
       Scene    mScene;
       Input    mInput;
       Loader   mLoader;
       Renderer mRenderer;
   };
}