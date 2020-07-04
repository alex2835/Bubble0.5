#pragma once

#include <string>
#include <vector>
#include <algorithm>

// spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// glew
#include "GL/glew.h"

// imgui
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


// engine
#include "application/application.h"
#include "log/log.h"
#include "entry_point.h"
#include "layers/layer.h"
#include "layers/layer_array.h"
#include "window/window.h"
