#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Logger {
public:
	static void init();
	inline static std::shared_ptr<spdlog::logger>& get_logger() { return s_Logger; }
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#define log_crit(...) ::Logger::get_logger()->critical(__VA_ARGS__)
#define log_error(...) ::Logger::get_logger()->error(__VA_ARGS__)
#define log_warn(...) ::Logger::get_logger()->warn(__VA_ARGS__)
#define log_info(...) ::Logger::get_logger()->info(__VA_ARGS__)
#define log_trace(...) ::Logger::get_logger()->trace(__VA_ARGS__)