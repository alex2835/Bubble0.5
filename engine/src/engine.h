#pragma once

// Engine core
#include "core/base.h"
#include "core/application/application.h"
#include "core/log/log.h"
#include "core/layers/layer.h"
#include "core/layers/layer_array.h"
#include "core/window/window.h"
#include "core/input/input.h"
#include "time/timer.h"

// Renderer
#include "renderer/renderer_base.h"
#include "renderer/framebuffer/framebuffer.h"
#include "renderer/buffer/buffer.h"
#include "renderer/vertex_array/vertex_array.h"
#include "renderer/shader/shader.h"
#include "renderer/shader/shader_loader.h"
#include "renderer/texture/texture.h"
#include "renderer/renderer/renderer.h"
#include "renderer/model/model_loader.h"
#include "renderer/light/light_array.h"
#include "renderer/cubemap/cubemap.h"
#include "renderer/skybox/skybox.h"
#include "renderer/skybox/skybox_loader.h"
#include "camera/camera.h"
#include "camera/free_camera.h"
#include "camera/target_camera.h"
#include "camera/third_person_camera.h"

// Scene
#include "scene/scene.h"
#include "scene/components.h"
#include "scene/entity/entity.h"
//#include "scene/entity/scriptable_entity.h"
