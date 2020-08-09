#pragma once

#include "base.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Bubble
{
	class Log
	{
		static Ref<spdlog::logger> client_logger;
		static Ref<spdlog::logger> core_logger;

	public:
		Log() = delete;
		
		static void init();
		
		inline static Ref<spdlog::logger>& GetLogger() { return client_logger; }
		inline static Ref<spdlog::logger>& GetCoreLogger() { return core_logger; }
	};
}

#define LOG_CORE_TRACE(...) ::Bubble::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)  ::Bubble::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)  ::Bubble::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Bubble::Log::GetCoreLogger()->error(__VA_ARGS__)

#define LOG_TRACE(...) ::Bubble::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  ::Bubble::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::Bubble::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Bubble::Log::GetLogger()->error(__VA_ARGS__)
