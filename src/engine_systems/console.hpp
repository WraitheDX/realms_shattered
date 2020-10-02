
#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#include <string>

#include "language.hpp"

class Console final {
public:
   Console();
   
   /*
   *  Return the width in number of character cells of the printable game area.
   */
   int width_get();
   
   /*
   *  Return the height in number of character cells of the printable game area.
   */
   int height_get();

   /*
   *  Clear the console screen of all characters.
   */
   void clear();

   /*
   *  Fill cursor_x/_y with the current coordinates of the console's cursor (carret).
   */
   void cursor_position_get( int &cursor_x, int &cursor_y );

   /*
   *  Change the coordinates of the console's cursor (carret) to cursor_x/_y.
   */
   void cursor_position_set( const int cursor_x, const int cursor_y );

   /*
   8  Pause the console and wait for the user to press a key.
   */
   void pause();

   /*
   *  Print the passed in 'text' at the console's current cursor position.
   */
   void print( const std::string &text );

   /*
   *  Print the passed in 'text' at the specified coordinates in the console.
   */
   void print( const std::string &text, const int cursor_x, const int cursor_y );

   /*
   *  Print a box of the specified character with the dimensions provided.
   * 
   *  The printing area is confined to the console's print dimensions.
   */
   void print_box( int position_x, int position_y, int width, int height, const char char_to_print );

   /*
   *  Print text formatted to stay withing the constraints of the specified dimensions.
   * 
   *  Returns the number of lines that were printed on, useful for relative positioning of further print calls.
   *  All printing done is also constrained within the bounds of the 'game screen'.
   */
   int print_formatted( const std::string &text, int position_x, int position_y, int width, int height );

private:
   int m_print_offset_x;
   int m_print_offset_y;

   int m_print_width_min;
   int m_print_height_min;
   int m_print_width;
   int m_print_height;

   /*
   *  Fills buffer_width/height with the number of character cells in width and height that make up the console buffer.
   */
   void buffer_dimensions_get( int &buffer_width, int &buffer_height );

   /*
   *  Breaks 'text' into a smaller string (&broken_line) with maximum length of 'length_max'.
   * 
   *  Returns position of line break within 'text'.
   */
   int find_text_break_point( const std::string &text, std::string &broken_line, const int length_max );
   
   /*
   *  Set the height of the game's printable area within the console
   */
   void printable_height_set( int height );

   /*
   *  Set the width of the game's printable area within the console
   */
   void printable_width_set( int width );

   /*
   *  Set the number of cells from the left of the console that the printable area will begin printing from.
   */
   void printable_offset_x_set( int offset_x );

   /*
   *  Set the number of cells from the top of the console that the printable area will begin printing from.
   */
   void printable_offset_y_set( int offset_y );

   /*
   *  Deletes all blanks spaces ' ' at the front of 'text'.
   */
   void text_remove_preceding_spaces( std::string &text );

   /*
   *  Set the title of the console window's title bar.
   */
   void title_set( const std::string &console_title );

   friend class GameState;
   friend class UserInput;
};

#endif _CONSOLE_HPP_
