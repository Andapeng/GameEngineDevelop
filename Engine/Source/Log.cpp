#include "Log.h"
//#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
// #include <boost/log/expressions.hpp>

void Logger::SetLogLevel(const std::string& levelName)
{
	// if (levelName == "debug")
	// {
	// 	boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
	// }
}

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

void Logger::LogTrace(const char* fmtstring)
{
	BOOST_LOG_TRIVIAL(trace) << fmtstring;
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

void Logger::LogTrace(std::string fmtstring)
{
	BOOST_LOG_TRIVIAL(trace) << fmtstring;
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

void Logger::LogTrace(std::wstring fmtstring)
{
	BOOST_LOG_TRIVIAL(trace) << fmtstring;
}
