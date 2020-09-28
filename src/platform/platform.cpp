
#include "platform.hpp"

const std::string &working_directory_get()
{
   // If working directory has already been obtained, use it.
   static std::string working_directory( "INVALID" );
   if( working_directory != "INVALID" ) {
      return working_directory;
   }

   #ifdef _WIN32
      working_directory = working_directory_get_win32();
   #endif // _WIN32

   return working_directory;
}

void console_buffer_dimensions_get( int &console_buffer_width, int &console_buffer_height )
{
   #ifdef _WIN32
      return console_buffer_dimensions_get_win32( console_buffer_width, console_buffer_height );
   #endif // _WIN32
}

void console_clear()
{
   #ifdef _WIN32
      return console_clear_win32();
   #endif // _WIN32
}

void console_cursor_position_get( int &cursor_x, int &cursor_y )
{
   #ifdef _WIN32
      return console_cursor_position_get_win32( cursor_x, cursor_y );
   #endif // _WIN32
}

void console_cursor_position_set( const int cursor_x, const int cursor_y )
{
   #ifdef _WIN32
      return console_cursor_position_set_win32( cursor_x, cursor_y );
   #endif // _WIN32
}

void console_pause()
{
   #ifdef _WIN32
      console_pause_win32();
   #endif // _WIN32
}

const bool console_title_set( const std::string &console_title )
{
   #ifdef _WIN32
      return console_title_set_win32( console_title );
   #endif // _WIN32

   return false;
}
