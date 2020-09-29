
#include "console.hpp"

#include <iostream>
#include "../platform/platform.hpp"

Console::Console( const std::string &console_title )
{
   console_title_set( console_title );
}

void Console::buffer_dimensions_get( int &buffer_width, int &buffer_height )
{
   console_buffer_dimensions_get( buffer_width, buffer_height );
}

int Console::buffer_height_get()
{
   int buffer_width = 0;
   int buffer_height = 0;
   console_buffer_dimensions_get( buffer_width, buffer_height );

   return buffer_height;
}

int Console::buffer_width_get()
{
   int buffer_width = 0;
   int buffer_height = 0;
   console_buffer_dimensions_get( buffer_width, buffer_height );

   return buffer_width;
}

void Console::clear()
{
   console_clear();
}

void Console::cursor_position_get( int &cursor_x, int &cursor_y )
{
   console_cursor_position_get( cursor_x, cursor_y );
}
  
void Console::cursor_position_set( const int cursor_x, const int cursor_y )
{
   console_cursor_position_set( cursor_x, cursor_y );
}

void Console::pause()
{
   console_pause();
}

void Console::print( const std::string &text )
{
   std::cout << text;
}

void Console::print( const std::string &text, const int cursor_x, const int cursor_y )
{
   console_cursor_position_set( cursor_x, cursor_y );

   std::cout << text;
}

void Console::title_set( const std::string &console_title )
{
   console_title_set( console_title );
}
