#pragma once

// Engine core
#include "core/base.h"
#include "core/application.h"
#include "core/log.h"
#include "core/layer.h"
#include "core/layer_array.h"
#include "core/window.h"
#include "core/input.h"
#include "core/timer.h"

// Renderer
#include "renderer/renderer_base.h"
#include "renderer/framebuffer.h"
#include "renderer/buffer.h"
#include "renderer/uniform_buffer.h"
#include "renderer/vertex_array.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/renderer.h"
#include "renderer/cubemap.h"
#include "renderer/skybox.h"
#include "renderer/camera.h"
#include "renderer/camera_free.h"
#include "renderer/camera_target.h"
#include "renderer/camera_third_person.h"

// Scene
#include "scene/scene.h"
#include "scene/entity.h"
#include "scene/components.h"

// Loader
#include "loader.h"


inline void InitEngine()
{
    Bubble::Skybox::Init();
    Bubble::Loader::Init();
    Bubble::Renderer::Init();
}