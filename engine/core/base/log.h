#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace Bubble
{
	class Log
	{
        static std::shared_ptr<spdlog::logger> sClientLogger;
        static std::shared_ptr<spdlog::logger> sCoreLogger;

	public:
		Log() = delete;
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetLogger()     { return sClientLogger; }
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
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