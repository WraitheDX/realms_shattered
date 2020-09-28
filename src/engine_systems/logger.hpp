
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <sstream>

enum class LoggerLevel {
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_PROGRESS,
	LOG_LEVEL_INFO
};

class Logger final {
public:
	Logger( const LoggerLevel p_message_level );
	~Logger();

	std::ostringstream & log();

	static void set_logger_level( const LoggerLevel logger_level );

private:
	static LoggerLevel m_logger_level;

	const LoggerLevel m_message_level;
	std::ostringstream m_message_stream;
};

#endif // _LOGGING_HPP_
