#include "Logging.h"

#include <cstdio>
#include <ctime>
#include <stdlib.h>

void LogMessage(LogLevel level, const char* prefix, const char* format, ...)
{
	// 1. Set Color based on level
	const char* color = "";
	switch (level)
	{
		case LogLevel::Warn:
			color = "\033[1;33m";
			break; // Yellow
		case LogLevel::Error:
			color = "\033[1;31m";
			break; // Red
		case LogLevel::Fatal:
			color = "\033[1;41m";
			break; // Red Background
		case LogLevel::Info:
			color = "\033[1;32m";
			break; // Green
		default:
			color = "\033[0m";
			break; // Reset
	}

	// 2. Print Time and Prefix
	time_t now = time(0);
	tm* ltm = localtime(&now);
	printf("%02d:%02d:%02d %s%s ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec, color, prefix);

	// 3. Print actual message
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	// 4. Reset color and newline
	printf("\033[0m\n");

	if (level == LogLevel::Fatal)
	{
		exit(0);
	}
}