
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <sstream>

/*
	Enumerations used for the different priority levels of messages passed to the logger.
*/
enum class LoggerLevel {
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_PROGRESS,
	LOG_LEVEL_INFO
};

/*
*	Logging class that reports time-stamped messages to the file 'log.txt'.
* 
*	Example usage:
*	Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Player's current health: " << player.get_health_current() << " should not go below 0!";
* 
*	Logger class should be called often to report progress through system initialization and clean-up functions. This is not a real-time game, and heavy
*	message logging could help catch simple bugs that might be confusing or go un-noticed for quite some time.
*	This implementation works by overloading the 'output string stream' method, which allows us to use the output operator '<<'. This is helpful in that
*	it gives us the functionality of 'printf' to inject variables anywhere we like in the string, without having to throw in '%' throughout the message.
*	The constructor takes in the message level, and after the call to Logger().log() the destructor is immediately called, appending a 'newline' character
*	to the message and writing it to 'log.txt'.
*/
class Logger final {
public:
	Logger( const LoggerLevel p_message_level );
	~Logger();

	/*
		Logging call that allows us to write our message that will be recorded.
	*/
	std::ostringstream &log();

	/*
		Should be called at application launch to ensure a fresh log file each run.
	*/
	static void create_new_log_file();

	/*
		Sets the level of logger messages you would like recorded to 'log.txt'.

		The logger will only report messages that are equal or lower in value to the logger_level.
	*/
	static void set_logger_level( const LoggerLevel logger_level );

private:
	static LoggerLevel m_logger_level;
	static std::string m_log_file_name;

	const LoggerLevel m_message_level;
	std::ostringstream m_message_stream;
};

#endif // _LOGGING_HPP_
