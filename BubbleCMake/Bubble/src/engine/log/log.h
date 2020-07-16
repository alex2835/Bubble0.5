#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Bubble
{
	struct Log
	{
		static std::shared_ptr<spdlog::logger> client_logger;
		static std::shared_ptr<spdlog::logger> core_logger;

		Log();

		~Log();

		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_logger() { return client_logger; }
		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return core_logger; }
	};
}

#define LOG_CORE_TRACE(...) ::Bubble::Log::get_core_logger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)  ::Bubble::Log::get_core_logger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)  ::Bubble::Log::get_core_logger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Bubble::Log::get_core_logger()->error(__VA_ARGS__)


#define LOG_TRACE(...) ::Bubble::Log::get_logger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  ::Bubble::Log::get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::Bubble::Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Bubble::Log::get_logger()->error(__VA_ARGS__)
