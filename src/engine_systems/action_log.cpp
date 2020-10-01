
#include "action_log.hpp"

#include "logger.hpp"

ActionLog::ActionLog() :
   m_log_display_size_current( 5 ),
   m_log_display_size_max( 20 ),
   m_log_lines()
{

}

// TODO (WraitheDX): Need to deal with lines that need to be broken into multiple lines
void ActionLog::add_line( const std::string &line )
{
   Logger( LoggerLevel::LOG_LEVEL_ACTION_LOG ).log() << line;

   m_log_lines.push_back( line );
   if( m_log_lines.size() >= m_log_display_size_max ) {
      m_log_lines.erase( m_log_lines.begin() );
   }
}

const int ActionLog::display_size_get()
{
   return m_log_display_size_current;
}
  
std::vector <std::string> &ActionLog::log_lines_get()
{
   return m_log_lines;
}
