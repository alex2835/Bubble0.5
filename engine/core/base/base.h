#pragma once

#include "log.h"
#include "lib/ref.h"
#include <memory>
#include <cassert>


// Assert
#ifdef BUBBLE_ASSERT_UNABLE
#define BUBBLE_ASSERT(x, ...)
#define BUBBLE_CORE_ASSERT(x, ...)
#else
#define BUBBLE_ASSERT(x, ...) { if (!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(false); } }
#define BUBBLE_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(false); } }
#endif

#define BIT(x) (1 << x)
