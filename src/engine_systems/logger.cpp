
#include "logger.hpp"

#include <ctime>

#include "file_io.hpp"

LoggerLevel Logger::m_logger_level = LoggerLevel::LOG_LEVEL_PROGRESS;

std::string Logger::m_log_file_name = "log.txt";

Logger::Logger( const LoggerLevel p_message_level ) :
   m_message_level( p_message_level )
{
   
}

Logger::~Logger()
{
	m_message_stream << std::endl;
   
   // Only report the message if it's log level is within the logger's log level
   if( m_message_level <= m_logger_level ) {
      FileIO::write_file( m_message_stream.str(), m_log_file_name, false );
   }
}

void Logger::create_new_log_file()
{
   FileIO::write_file( "    Shattered Realms Log\n===========================\n\n", m_log_file_name, true );
}

std::ostringstream & Logger::log()
{
   // Obtain the current time
   std::time_t l_time( std::time( 0 ) );
   // Convert the current time into something more easily handled
   std::tm l_current_time;
   localtime_s( &l_current_time, &l_time );

   // Append the month, adding 0 if needed to keep uniform alignment
   if( ( l_current_time.tm_mon + 1 ) < 10 ) {
      m_message_stream << 0;
   }
   m_message_stream << ( l_current_time.tm_mon + 1 ) << "/";

   // Append day, adding 0 if needed to keep uniform alignment
   if( l_current_time.tm_mday < 10 ) {
      m_message_stream << 0;
   }
   m_message_stream << l_current_time.tm_mday << " ";

   // Append hour, adding 0 if needed to keep uniform alignment
   if( l_current_time.tm_hour < 10 ) {
      m_message_stream << 0;
   }
   m_message_stream << l_current_time.tm_hour << ":";

   // Append minutes, adding 0 if needed to keep uniform alignment
   if( l_current_time.tm_min < 10 ) {
      m_message_stream << 0;
   }
   m_message_stream << l_current_time.tm_min << ":";

   // Append seconds, adding 0 if needed to keep uniform alignment
   if( l_current_time.tm_sec < 10 )
   {
      m_message_stream << 0;
   }
   m_message_stream << l_current_time.tm_sec << " ";

   // Append message log level
   switch( m_message_level ) {
      case LoggerLevel::LOG_LEVEL_ERROR:
         m_message_stream << "**ERROR**: ";
         break;
      case LoggerLevel::LOG_LEVEL_WARNING:
         m_message_stream << "!WARNING!: ";
         break;
      case LoggerLevel::LOG_LEVEL_PROGRESS:
         m_message_stream << "~PROGRESS: ";
         break;
      case LoggerLevel::LOG_LEVEL_INFO:
         m_message_stream << "--INFO---: ";
         break;
   }

   return m_message_stream;
}

void Logger::set_logger_level( const LoggerLevel logger_level )
{
   m_logger_level = logger_level;
}
