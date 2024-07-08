#pragma once
#include <string>
class Logger
{
public:
	static void LogError(const char* fmtstring);
	static void LogWarning(const char* fmtstring);
	static void LogInfo(const char* fmtstring);

	static void LogError(std::string fmtstring);
	static void LogWarning(std::string fmtstring);
	static void LogInfo(std::string fmtstring);
};
