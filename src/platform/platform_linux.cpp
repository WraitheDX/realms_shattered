
#include "platform_linux.hpp"
#include "../engine_systems/logger.hpp"

#ifdef __linux__


const std::string working_directory_get_linux()
{
   std::string working_directory;
   
   char buffer[PATH_MAX];
   getcwd(buffer, PATH_MAX);
   working_directory = buffer;

   return working_directory;
}

void console_buffer_dimensions_get_linux( int &console_buffer_width, int &console_buffer_height )
{
    // Obtain console size using ioctl.
   struct winsize screen_size;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_size);
  
   console_buffer_width = screen_size.ws_col;
   console_buffer_height = screen_size.ws_row;
}

void console_clear_linux()
{
   system( "clear" );
}

// TODO (WraitheDX): Constrain cursor position to dimensions of the console window.
void console_cursor_position_set_linux( const int cursor_x, const int cursor_y )
{
    printf("%c[%d;%df",0x1B,cursor_y,cursor_x);
}

void console_pause_linux()
{
   system( "read -rsp $'Press any key to continue . . .\n'" );
}

#endif // __linux__
