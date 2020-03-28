#include <pch.h>
#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::init() {
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_Logger = spdlog::stdout_color_mt("CoffeeMug");

	#ifdef DEBUG
	s_Logger->set_level(spdlog::level::trace);
	#else
	s_Logger->set_level(spdlog::level::info);
	#endif
}
