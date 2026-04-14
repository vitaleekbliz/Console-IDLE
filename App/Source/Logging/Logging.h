#pragma once
#include <cstdarg>

enum class LogLevel : char
{
	Trace,
	Info,
	Warn,
	Error,
	Fatal
};

void LogMessage(LogLevel level, const char* prefix, const char* format, ...);

// The Macros
#ifdef DEBUG
	#define ENABLE_LOGGING 1
	#define ENABLE_TRACE 1
#elif defined(RELEASE)
	#define ENABLE_LOGGING 1
	#define ENABLE_TRACE 0	 // No trace in Release
#elif						 // Distribution
	#define ENABLE_LOGGING 0 // No logs in Dist (max performance)
	#define ENABLE_TRACE 0
#endif

#if ENABLE_TRACE
	#define APP_TRACE(...) LogMessage(LogLevel::Trace, "[TRACE]", __VA_ARGS__)
#else
	#define APP_TRACE(...)
#endif

#if ENABLE_LOGGING
	#define APP_INFO(...) LogMessage(LogLevel::Info, "[INFO] ", __VA_ARGS__)
#else
	#define APP_INFO(...)
#endif

#define APP_WARN(...) LogMessage(LogLevel::Warn, "[WARN] ", __VA_ARGS__)
#define APP_ERROR(...) LogMessage(LogLevel::Error, "[ERROR]", __VA_ARGS__)
#define APP_FATAL(...) LogMessage(LogLevel::Fatal, "[FATAL]", __VA_ARGS__)