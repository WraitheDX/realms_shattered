
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

   #ifdef __linux__
      working_directory = working_directory_get_linux();
   #endif // __linux__
   return working_directory;
}

void console_buffer_dimensions_get( int &console_buffer_width, int &console_buffer_height )
{
   #ifdef _WIN32
      return console_buffer_dimensions_get_win32( console_buffer_width, console_buffer_height );
   #endif // _WIN32

   #ifdef __linux__
      return console_buffer_dimensions_get_linux( console_buffer_width, console_buffer_height );
   #endif // __linux__

}

void console_clear()
{
   #ifdef _WIN32
      return console_clear_win32();
   #endif // _WIN32

   #ifdef __linux__
      return console_clear_linux();
   #endif // __linux__

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

   #ifdef __linux__
      return console_cursor_position_set_linux( cursor_x, cursor_y );
   #endif // __linux__
}

void console_pause()
{
   #ifdef _WIN32
      console_pause_win32();
   #endif // _WIN32

   #ifdef __linux__
      console_pause_linux();
   #endif // __linux__
}

const bool console_title_set( const std::string &console_title )
{
   #ifdef _WIN32
      return console_title_set_win32( console_title );
   #endif // _WIN32

   return false;
}

const bool get_file_list( std::vector <std::string> &file_list, const std::string &file_path )
{
   #ifdef _WIN32
      return get_file_list_win32( file_list, file_path );
   #endif // _WIN32

   #ifdef __linux__
      get_file_list_linux( file_list, file_path );
   #endif // __linux__

   return false;
}

void folder_create_platform( const std::string &folder_path )
{
   #ifdef _WIN32
      folder_create_win32( folder_path );
   #endif // _WIN32
}

const bool folder_exists_check( const std::string &folder_path )
{
   #ifdef _WIN32
      return folder_exists_check_win32( folder_path );
   #endif // _WIN32

   return false;
}
