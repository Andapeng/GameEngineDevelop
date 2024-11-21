#include "Log.h"
#include <boost/log/trivial.hpp>

void Logger::LogError(const char* fmtstring)
{
	BOOST_LOG_TRIVIAL(error) << fmtstring;
}

void Logger::LogWarning(const char* fmtstring)
{
	BOOST_LOG_TRIVIAL(warning) << fmtstring;
}

void Logger::LogInfo(const char* fmtstring)
{
	BOOST_LOG_TRIVIAL(info) << fmtstring;
}

void Logger::LogError(std::string fmtstring)
{
	BOOST_LOG_TRIVIAL(error) << fmtstring;
}

void Logger::LogWarning(std::string fmtstring)
{
	BOOST_LOG_TRIVIAL(warning) << fmtstring;
}

void Logger::LogInfo(std::string fmtstring)
{
	BOOST_LOG_TRIVIAL(info) << fmtstring;
}

void Logger::LogError(std::wstring fmtstring)
{
	BOOST_LOG_TRIVIAL(error) << fmtstring;
}

void Logger::LogWarning(std::wstring fmtstring)
{
	BOOST_LOG_TRIVIAL(warning) << fmtstring;
}

void Logger::LogInfo(std::wstring fmtstring)
{
	BOOST_LOG_TRIVIAL(info) << fmtstring;
}
