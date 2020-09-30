
#include "console.hpp"

#include <iostream>

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

void Console::title_set( const std::string &console_title )
{
   console_title_set( console_title );
}
