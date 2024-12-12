#pragma once
#include <string>
class Logger
{
public:

	static void SetLogLevel(const std::string& levelName);

	static void LogError(const char* fmtstring);
	static void LogWarning(const char* fmtstring);
	static void LogInfo(const char* fmtstring);
	static void LogTrace(const char* fmtstring);

	static void LogError(std::string fmtstring);
	static void LogWarning(std::string fmtstring);
	static void LogInfo(std::string fmtstring);
	static void LogTrace(std::string fmtstring);


	static void LogError(std::wstring fmtstring);
	static void LogWarning(std::wstring fmtstring);
	static void LogInfo(std::wstring fmtstring);
	static void LogTrace(std::wstring fmtstring);

};
