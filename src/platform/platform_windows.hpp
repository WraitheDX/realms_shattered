
#ifndef _PLATFORM_WINDOWS_HPP_
#define _PLATFORM_WINDOWS_HPP_

#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>

/*
   Obtains the execution path of the game from the Windows platform libraries.

   Currently does not check to ensure a path is actually obtained.
*/
const std::string working_directory_get_win32();

/*
   Gets the current dimensions of the console buffer from the Windows platform libraries.
*/
void console_buffer_dimensions_get_win32( int &console_buffer_width, int &console_buffer_height );

/*
   Clears the console screen from the Windows platform libraries.
*/
void console_clear_win32();

/*
   Gets the current cursor position from the Windows platform libraries.
*/
void console_cursor_position_get_win32( int &cursor_x, int &cursor_y );

/*
   Sets the cursor position from the Windows platform libraries.
*/
void console_cursor_position_set_win32( const int cursor_x, const int cursor_y );

/*
   Uses the Windows platform libraries to pause the console and wait for the player to press a key.
*/
void console_pause_win32();

/*
   Sets the title of the console window from the Windows platform libraries.
*/
const bool console_title_set_win32( const std::string &console_title );

/*
*  Returns file_list populated with all files found in file_path.
*/
const bool get_file_list_win32( std::vector <std::string> &file_list, const std::string &file_path );

/*
*  Creates the fold specified.
*/
void folder_create_win32( const std::string &folder_path );

/*
*  Returns true if folder_path exists.
*/
const bool folder_exists_check_win32( const std::string &folder_path );

#endif // _WIN32

#endif // _PLATFORM_WINDOWS_HPP_
