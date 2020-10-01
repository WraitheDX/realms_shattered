
#ifndef _ACTION_LOG_HPP_
#define _ACTION_LOG_HPP_

#include <string>
#include <vector>

#include "console.hpp"

class ActionLog final {
public:
   ActionLog();

   /*
   *  Add a line of text to the ActionLog.
   * 
   *  The newest line will be displayed at the top of the log.
   */
   void add_line( const std::string &line );

   /*
   *  Return the current size of the ActionLog's display.
   */
   const int display_size_get();

   /*
   *  Return the lines of the action log.
   */
   std::vector <std::string> &log_lines_get();

private:
   int m_log_display_size_current;
   int m_log_display_size_max;

   std::vector <std::string> m_log_lines;
};

#endif // _ACTION_LOG_HPP_
