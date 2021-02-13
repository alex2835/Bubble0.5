
#include "log.h"

namespace Bubble
{
	std::shared_ptr<spdlog::logger> Log::sClientLogger;
	std::shared_ptr<spdlog::logger> Log::sCoreLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		sCoreLogger = spdlog::stdout_color_mt("Engine");
		sCoreLogger->set_level(spdlog::level::trace);
		
		sClientLogger = spdlog::stdout_color_mt("APP");
		sClientLogger->set_level(spdlog::level::trace);
	}
}