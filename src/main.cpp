
#include <iostream>
#include <string>

#include "engine_systems/console.hpp"
#include "engine_systems/language.hpp"
#include "engine_systems/logger.hpp"

int main( char ** argument_strings, int argument_count )
{
   // Start the initialization of the game by setting up the Logger class to log game data and errors for us.
   Logger::set_logger_level( LoggerLevel::LOG_LEVEL_INFO );
   Logger::create_new_log_file();

   // The game is now ready to initialize the systems that allow the engine to run the game.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initializing";

   const std::string GAME_TITLE = "Realms Shattered v0.0";
   Console console( GAME_TITLE );

   int buffer_width = 0;
   int buffer_height = 0;
   console.buffer_dimensions_get( buffer_width, buffer_height );

   int command_text_position_y = 20;

   Language language;
   language.commands_load( "data/language/en_commands.txt" );
   language.text_load( "data/language/en_game_text.txt" );

   // The game is now initialized and ready to begin the gameplay loop.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";

   bool game_running = true;
   while( game_running ) {
      console.print( GAME_TITLE, ( ( buffer_width / 2 ) - ( GAME_TITLE.length() / 2 ) ), 1 );

      console.cursor_position_set( 0, command_text_position_y );
      std::cout << language.text_tag_get( "tag_help_command_hint" ) << "\n";
      std::cout << language.text_tag_get( "tag_command" ) << ": ";
      std::string user_input( "" );
      std::getline( std::cin, user_input );
      std::cout << "\n";
      
      switch( language.command_tag_get( user_input ) ) {
         case CommandTag::COMMAND_INVALID:
            break;
         case CommandTag::COMMAND_HELP:
            console.cursor_position_set( 0, 10 );
            std::cout << language.text_tag_get( "tag_help_command_list" ) << "\n";
            std::cout << language.text_tag_get( "tag_help_command_list_note" ) << "\n\n";
            std::cout << language.text_tag_get( "tag_help_command_list_quit" ) << "\n";
            break;
         case CommandTag::COMMAND_QUIT:
            game_running = false;
            break;
      }
      
      console.cursor_position_set( 0, command_text_position_y + 2 );
      console.pause();
      console.clear();
   }

   // The game has now left the gameplay loop and will shut down any systems that require being shut down.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is shutting down";

   return 0;
}
