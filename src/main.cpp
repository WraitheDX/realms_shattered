
#include <iostream>
#include <string>

#include "engine_systems/console.hpp"
#include "engine_systems/game_data.hpp"
#include "engine_systems/language.hpp"
#include "engine_systems/logger.hpp"
#include "engine_systems/user_input.hpp"
#include "engine_systems/user_interface.hpp"

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

   Language language;
   language.commands_load( "data/language/en_commands.txt" );
   language.text_load( "data/language/en_game_text.txt" );

   UserInput user_input;
   UserInterface user_interface;
   GameData game_data;

   // The game is now initialized and ready to begin the gameplay loop.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";

   user_input.player_name_get( console, language, game_data );

   bool game_running = true;
   while( game_running ) {
      console.print( GAME_TITLE, ( ( buffer_width / 2 ) - ( GAME_TITLE.length() / 2 ) ), 1 );

      user_interface.player_stats_brief_display( console, language, game_data );
      user_interface.command_prompt_display( console, language );
      CommandTag command_tag( user_input.player_command_get( language ) );
      
      switch( command_tag ) {
         case CommandTag::COMMAND_INVALID:
            break;
         case CommandTag::COMMAND_HELP:
            user_interface.help_list_display( console, language );
            break;
         case CommandTag::COMMAND_QUIT:
            game_running = false;
            break;
      }
      
      user_interface.pause_and_display_message( console );
      console.clear();
   }

   // The game has now left the gameplay loop and will shut down any systems that require being shut down.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is shutting down";

   return 0;
}
