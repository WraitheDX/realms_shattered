
#include "platform_windows.hpp"

#include "../engine_systems/logger.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>

const std::string working_directory_get_win32()
{
   std::string working_directory;
   #ifdef _WIN32
   {
      char buffer[FILENAME_MAX];
      // The Windows call: get(c)urrent(w)orking(d)irectory
      char *temp( _getcwd( buffer, FILENAME_MAX ) );

      working_directory = buffer;
   }
   #endif // _WIN32

   return working_directory;
}

void console_buffer_dimensions_get_win32( int &console_buffer_width, int &console_buffer_height )
{
   // Get handle to Win32 console output
   HANDLE console_handle( GetStdHandle( STD_OUTPUT_HANDLE ) );
   if( console_handle == nullptr )
   {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Failed to get console buffer dimensions (Win32) - GetStdHandle() has failed";
      return;
   }

   // Obtain Win32 screen buffer information which will provide us with the console's buffer dimensions.
   CONSOLE_SCREEN_BUFFER_INFO console_buffer_info;
   if( GetConsoleScreenBufferInfo( console_handle, &console_buffer_info ) == 0 )
   {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Failed to get console cursor position (Win32) - GetConsoleScreenBufferInfo() has failed";
      return;
   }

   console_buffer_width = console_buffer_info.dwSize.X;
   console_buffer_height = console_buffer_info.dwSize.Y;
}

void console_clear_win32()
{
   system( "cls" );
}

void console_cursor_position_get_win32( int & cursor_x, int & cursor_y )
{
   // Get Win32 handle to console window output
   HANDLE console_handle( GetStdHandle( STD_OUTPUT_HANDLE ) );
   if( console_handle == nullptr )
   {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Failed to get console cursor position (Win32) - GetStdHandle() has failed";
      return;
   }
   
   // Obtain Win32 screen buffer information which will provide us with the console cursor's position.
   CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
   if( GetConsoleScreenBufferInfo( console_handle, &console_screen_buffer_info ) == 0 )
   {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Failed to get console cursor position (Win32) - GetConsoleScreenBufferInfo() has failed";
      return;
   }

   // Grab position data of console cursor
   cursor_x = console_screen_buffer_info.dwCursorPosition.X;
   cursor_y = console_screen_buffer_info.dwCursorPosition.Y;
}

// TODO (WraitheDX): Constrain cursor position to dimensions of the console window.
void console_cursor_position_set_win32( const int cursor_x, const int cursor_y )
{
   // Get Win32 handle to console window output
   HANDLE console_handle( GetStdHandle( STD_OUTPUT_HANDLE ) );
   if( console_handle == nullptr )
   {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Failed to set console cursor position (Win32) - GetStdHandle() has failed";
      return;
   }

   COORD cursor_coordinates;
   cursor_coordinates.X = cursor_x;
   cursor_coordinates.Y = cursor_y;
   SetConsoleCursorPosition( console_handle, cursor_coordinates );
}

void console_pause_win32()
{
   system( "pause" );
}

const bool console_title_set_win32( const std::string &console_title )
{
   // The Windows call SetConsoleTitle specifically takes a (L)ong(P)ointer to (C)onstant(T)char(STR)ing
   if( !SetConsoleTitleA( console_title.c_str() ) )
   {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "set_console_title_win32() failed.";
      return false;
   }
  
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Console title set to: " << console_title;
   return true;
}

const bool get_file_list_win32( std::vector <std::string> &file_list, const std::string &file_path )
{
   return false;
}

#endif // _WIN32
