
#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#include <string>
#include <vector>

#include "platform_windows.hpp"
#include "platform_linux.hpp"
/*
*  Returns the platform-specific call to get_working_directory.
*
*  Obtains the current execution directory of the game.
*/
const std::string &working_directory_get();

/*
*  Gets the current dimensions of the console buffer.
*
*  Fills console_buffer_width/height with the width and height of the console's buffer.
*/
void console_buffer_dimensions_get( int &console_buffer_width, int &console_buffer_height );

/*
*  Returns the platform-specific call to console_clear_screen.
*
*  Clears the screen buffer of all characters.
*/
void console_clear();

/*
*  Returns the platform-specific call to console_cursor_position_get.
*
*  Fills cursor_x/_y with the current x and y position of the console's cursor (carret).
*/
void console_cursor_position_get( int &cursor_x, int &cursor_y );

/*
*  Returns the platform-specific call to console_cursor_position_set.
*
*  Sets the position of the console's cursor (carret) to the specified x/y coordinates in the console.
*/
void console_cursor_position_set( const int cursor_x, const int cursor_y );

/*
*  Returns the platform-specific call to console_pause.
* 
*  Causes the console to pause and wait for the player to press a key.
*/
void console_pause();

/*
*  Returns the platform-specific call to set_console_title.
*/
const bool console_title_set( const std::string &console_title );

/*
*  Returns the platform-specific call to get_file_list.
*/
const bool get_file_list( std::vector <std::string> &file_list, const std::string &file_path );

#endif // _PLATFORM_HPP_
