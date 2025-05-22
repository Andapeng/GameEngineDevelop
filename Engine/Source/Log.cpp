#include "Log.h"
#include <iostream>
#include <boost/log/core/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
void Logger::Initialize()
{
    // Initialize the logging library
    // 添加文件日志后端
    logging::add_file_log(
      keywords::file_name = "sample_%N.log",      // 文件名模式
      keywords::rotation_size = 10 * 1024 * 1024, // 每10MB轮转一次
      keywords::time_based_rotation =
        sinks::file::rotation_at_time_point(0, 0, 0), // 每天午夜轮转
      keywords::format = "[%TimeStamp%]: %Message%"   // 日志格式
    );

	    // 添加控制台日志后端
    logging::add_console_log(std::cout,
                             keywords::format = "[%TimeStamp%]: %Message%");

    // 添加常用属性(如时间戳)
    logging::add_common_attributes();

	// // 设置日志级别
    logging::core::get()->set_filter(logging::trivial::severity >=
                                  logging::trivial::debug);

}

void
Logger::SetLogLevel(const char* LogLevelName)
{
    if (LogLevelName == "Debug") {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                            boost::log::trivial::debug);
    } else if (LogLevelName == "Info") {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                            boost::log::trivial::info);
    } else if (LogLevelName == "Warning") {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                            boost::log::trivial::warning);
    } else if (LogLevelName == "Error") {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                            boost::log::trivial::error);
    } else if (LogLevelName == "Fatal") {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                            boost::log::trivial::fatal);
    }
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
