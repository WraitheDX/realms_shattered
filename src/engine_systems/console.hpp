
#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#include <string>

class Console final {
public:
   /*
      Fills buffer_width/height with the number of character cells in width and height that make up the console buffer.
   */
   void buffer_dimensions_get( int &buffer_width, int &buffer_height );
   
   /*
      Return the width in number of character cells of the console buffer.
   */
   int buffer_width_get();
   
   /*
      Return the height in number of character cells of the console buffer.
   */
   int buffer_height_get();

   /*
      Clear the console screen of all characters.
   */
   void clear();

   /*
      Fill cursor_x/_y with the current coordinates of the console's cursor (carret).
   */
   void cursor_position_get( int &cursor_x, int &cursor_y );

   /*
      Change the coordinates of the console's cursor (carret) to cursor_x/_y.
   */
   void cursor_position_set( const int cursor_x, const int cursor_y );

   /*
      Pause the console and wait for the user to press a key.
   */
   void pause();

   /*
      Print the passed in 'text' at the console's current cursor position.
   */
   void print( const std::string &text );

   /*
      Print the passed in 'text' at the specified coordinates in the console.
   */
   void print( const std::string &text, const int cursor_x, const int cursor_y );

   /*
      Set the title of the console window's title bar.
   */
   void title_set( const std::string &console_title );

private:

};

#endif _CONSOLE_HPP_
