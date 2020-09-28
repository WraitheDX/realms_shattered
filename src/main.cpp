
#include <iostream>
#include <string>

#include "engine_systems/logger.hpp"
#include "engine_systems/console.hpp"

int main( char ** argument_strings, int argument_count )
{
   // Start the initialization of the game by setting up the Logger class to log game data and errors for us.
   Logger::set_logger_level( LoggerLevel::LOG_LEVEL_INFO );
   Logger::create_new_log_file();

   // The game is now ready to initialize the systems that allow the engine to run the game.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initializing";

   const std::string GAME_TITLE = "Shattered Realms v0.0";
   Console console( GAME_TITLE );

   int buffer_width = 0;
   int buffer_height = 0;
   console.buffer_dimensions_get( buffer_width, buffer_height );

   // The game is now initialized and ready to begin the gameplay loop.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";

   console.print( GAME_TITLE, ( ( buffer_width / 2 ) - ( GAME_TITLE.length() / 2 ) ), 1 );
   console.cursor_position_set( 0, 20 );
   std::cout << "Console dimensions are: " << buffer_width << "." << buffer_height << "\n\n";

   console.pause();
   console.clear();
   console.print( "Thank you for playing!\n\n", ( ( buffer_width / 2 ) - 10 ), 1 );
   console.pause();

   // The game has now left the gameplay loop and will shut down any systems that require being shut down.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is shutting down";

   return 0;
}
