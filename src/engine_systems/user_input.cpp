
#include "user_input.hpp"

#include <iostream>
#include <string>

#include "logger.hpp"
#include "../entities/actor.hpp"

const CommandTag UserInput::player_command_get( Language &language )
{
   std::string user_input( "" );
   // Getline allows us to read the entirety of the player's input, including spaces.
   std::getline( std::cin, user_input );
   std::cout << "\n";

   CommandTag command_tag = language.command_tag_get( user_input );
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player typed: " << user_input << ", found ID: " << int( command_tag );
   return command_tag;
}

void UserInput::player_name_get( Console &console, Language &language, GameData &game_data )
{
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Asking player for name";

   static const int TEXT_ENTER_NAME_POSITION_Y( 1 );

   while( true ) {
      console.cursor_position_set( 0, TEXT_ENTER_NAME_POSITION_Y );
      std::cout << language.text_tag_get( "tag_name_entry" ) << "\n"
                << "> ";

      std::string name( "" );
      std::getline( std::cin, name );

      console.clear();

      if( name.empty() ) {
         continue;
      }

      game_data.player_get()->name_set( name );
      Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player entered name: " << game_data.player_get()->name_get();
      break;
   }
}
