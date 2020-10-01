
#ifndef _PLATFORM_LINUX_HPP_
#define _PLATFORM_LINUX_HPP_

#include <string>
#include <vector>

#ifdef __linux__
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/limits.h>

/*
   Obtains the execution path of the game from C standard library functions
*/
const std::string working_directory_get_linux();

/*
   Gets the current dimensions of the console bugger using ioctl.
*/
void console_buffer_dimensions_get_linux( int &console_buffer_width, int &console_buffer_height );

/*
    Uses the shell command "clear" to clear the screen.
*/
void console_clear_linux();

/*
    TODO: Find a way to do this in Linux. 
*/
void console_cursor_position_get_linux( int &cursor_x, int &cursor_y );

/*
   Sets the cursor position using printf.
*/
void console_cursor_position_set_linux( const int cursor_x, const int cursor_y );

/*
   Uses the shell command "read" to behave like DOS' "pause". 
*/
void console_pause_linux();

/*
    TODO: Find a way to do this in Linux.
*/
const bool console_title_set_linux( const std::string &console_title );

/*
*  Returns file_list populated with all files found in file_path.
*/
const bool get_file_list_linux( std::vector <std::string> &file_list, const std::string &file_path );

#endif // _WIN32

#endif // _PLATFORM_LINUX_HPP_
