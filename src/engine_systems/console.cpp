
#include "console.hpp"

#include <iostream>
#include <vector>

#include "logger.hpp"
#include "../platform/platform.hpp"

Console::Console() :
   m_print_offset_x( 0 ),
   m_print_offset_y( 0 ),
   m_print_width_min( 80 ),
   m_print_height_min( 20 ),
   m_print_width( m_print_width_min ),
   m_print_height( m_print_height_min )
{
   
}

void Console::buffer_dimensions_get( int &buffer_width, int &buffer_height )
{
   console_buffer_dimensions_get( buffer_width, buffer_height );
}

int Console::height_get()
{
   return m_print_height;
}

int Console::width_get() {
   return m_print_width;
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

int Console::find_text_break_point( const std::string &text, std::string &broken_line, const int length_max )
{
   for( int text_iterator( length_max ); text_iterator >= 0; --text_iterator ) {
      char current_character( text[ text_iterator ] );
      if( current_character == ' ' ) {
         broken_line = text.substr( 0, text_iterator );
         return text_iterator + 1;
      }
      
      if( current_character == ',' || current_character == '.' ) {
         broken_line = text.substr( 0, text_iterator + 1 );
         return text_iterator + 1;
      }
   }
   
   // If no acceptable break-points are found within the allowed length, break the string at max allowed length.
   broken_line = text.substr( 0, length_max );
   return length_max;
}

void Console::pause()
{
   print( "", ( ( m_print_width / 2 ) - 14 ), m_print_height - 1 );
   console_pause();
}

void Console::print( const std::string &text )
{
   int cursor_x( 0 );
   int cursor_y( 0 );
   cursor_position_get( cursor_x, cursor_y );

   bool cursor_reposition( false );
   if( cursor_x < m_print_offset_x ) {
      cursor_x = m_print_offset_x;
      cursor_reposition = true;
   } else if( cursor_x > ( m_print_offset_x + m_print_width ) ) {
      cursor_x = ( m_print_offset_x + m_print_width - 1 );
      cursor_reposition = true;
   }

   if( cursor_y < m_print_offset_y ) {
      cursor_y = m_print_offset_y;
      cursor_reposition = true;
   } else if( cursor_y > ( m_print_offset_y + m_print_height ) ) {
      cursor_y = ( m_print_offset_y + m_print_height - 1 );
      cursor_reposition = true;
   }

   if( cursor_reposition ) {
      cursor_position_set( cursor_x, cursor_y );
   }

   if( ( int( text.length() ) + cursor_x ) >= ( m_print_width + m_print_offset_x ) ) {
      std::cout << text.substr( 0, ( ( m_print_width + m_print_offset_x ) - cursor_x ) );
   } else {
      std::cout << text;
   }
}

void Console::print( const std::string &text, const int cursor_x, const int cursor_y )
{
   console_cursor_position_set( cursor_x + m_print_offset_x, cursor_y + m_print_offset_y );

   print( text );
}
  
void Console::print_box( int position_x, int position_y, int width, int height, const char char_to_print )
{
   int console_buffer_width( 0 );
   int console_buffer_height( 0 );
   console_buffer_dimensions_get( console_buffer_width, console_buffer_height );

   position_x += m_print_offset_x;
   position_y += m_print_offset_y;

   if( position_x > console_buffer_width ) {
      Logger( LoggerLevel::LOG_LEVEL_WARNING ).log() << "Console::print_box() received position_x value that is out of bounds";
      return;
   }

   if( position_y > console_buffer_height ) {
      Logger( LoggerLevel::LOG_LEVEL_WARNING ).log() << "Console::print_box() received position_y value that is out of bounds";
      return;
   }

   if( ( width + position_x ) > console_buffer_width ) {
      width -= ( ( width + position_x ) - console_buffer_width );
   }
   
   if( width <= 0 ) {
      Logger( LoggerLevel::LOG_LEVEL_WARNING ).log() << "Console::print_box() received width value that is not viable";
      return;
   }

   if( ( height + position_y ) > console_buffer_height ) {
      height = ( console_buffer_height - position_y );
   }
   
   if( height <= 0 ) {
      Logger( LoggerLevel::LOG_LEVEL_WARNING ).log() << "Console::print_box() received height value that is not viable";
      return;
   }

   for( int iterator_y( 0 ); iterator_y < height; ++iterator_y ) {
      cursor_position_set( position_x, ( position_y + iterator_y ) );
      if( iterator_y == 0 || iterator_y == ( height - 1 ) ) {
         for( int iterator_x( 0 ); iterator_x < width; ++iterator_x ) {
            std::cout << char_to_print;
         }

         continue;
      }

      std::cout << char_to_print;
      
      cursor_position_set( ( position_x + width - 1 ), ( position_y + iterator_y ) );
      std::cout << char_to_print;
   }
}
 
// This function takes in a const string reference because the while loop will erase the contents of the string,
// and the user might want to use the string, or its original length, after this call. The const declaration forces
// us to create our own copy of the string.
int Console::print_formatted( const std::string &text, int position_x, int position_y, int width, int height )
{
   std::vector <std::string> text_lines;

   std::string text_to_format( text );
   while( !text_to_format.empty() ) {
      // If the text remaining to print is shorter than the requested width, append it to printable vector and break from the loop.
      if( width > text_to_format.length() ) {
         text_remove_preceding_spaces( text_to_format );
         text_lines.push_back( text_to_format );
         break;
      }

      std::string broken_line( "" );
      int space_position( find_text_break_point( text_to_format, broken_line, width ) );
      text_lines.push_back( broken_line );
      text_to_format.erase( 0, space_position );

      // If the number of lines to print meets or exceeds the allowed height, break from the loop to print.
      if( text_lines.size() >= height ) {
         break;
      }
   }

   // Iterate through the vector of text and print to screen.
   for( int iterator_y( 0 ); iterator_y < height; ++ iterator_y ) {
      print( text_lines[ iterator_y ], position_x, ( position_y + iterator_y ) );
   }

   return text_lines.size();
}

void Console::printable_height_set( int height ) {
   int console_buffer_width( 0 );
   int console_buffer_height( 0 );
   buffer_dimensions_get( console_buffer_width, console_buffer_height );

   if( height < m_print_height_min ) {
      m_print_height = m_print_height_min;
   } else if( height > console_buffer_height ) {
      m_print_height = console_buffer_height - 1;
   } else {
      m_print_height = height;
   }
}

void Console::printable_width_set( int width ) {
   int console_buffer_width( 0 );
   int console_buffer_height( 0 );
   buffer_dimensions_get( console_buffer_width, console_buffer_height );

   if( width < m_print_width_min ) {
      m_print_width = m_print_width_min;
   } else if( width > console_buffer_width ) {
      m_print_width = console_buffer_width - 1;
   } else {
      m_print_width = width;
   }
}

void Console::printable_offset_x_set( int offset_x )
{
   int console_buffer_width( 0 );
   int console_buffer_height( 0 );
   buffer_dimensions_get( console_buffer_width, console_buffer_height );

   if( offset_x < 0 ) {
      m_print_offset_x = 0;
   } else if( offset_x > ( console_buffer_width - m_print_width ) ) {
      m_print_offset_x = ( console_buffer_width - m_print_width );
   } else {
      m_print_offset_x = offset_x;
   }
}

void Console::printable_offset_y_set( int offset_y )
{
   int console_buffer_width( 0 );
   int console_buffer_height( 0 );
   buffer_dimensions_get( console_buffer_width, console_buffer_height );

   if( offset_y < 0 ) {
      m_print_offset_y = 0;
   } else if( offset_y > ( console_buffer_height - m_print_height ) ) {
      m_print_offset_y = ( console_buffer_height - m_print_height );
   } else {
      m_print_offset_y = offset_y;
   }
}

void Console::text_remove_preceding_spaces( std::string &text )
{
   for( int text_iterator( 0 ); text_iterator < text.size(); ++text_iterator ) {
      if( text[ 0 ] == ' ' ) {
         text.erase( 0, 1 );
      } else {
         return;
      }
   }
}

void Console::title_set( const std::string &console_title )
{
   console_title_set( console_title );
}
