
#include "user_input.hpp"

#include <iostream>
#include <string>

#include "logger.hpp"

const CommandTag UserInput::player_command_get( Language &language )
{
   std::string user_input( "" );
   // Getline allows us to read the entirety of the player's input, including spaces.
   std::getline( std::cin, user_input );

   CommandTag command_tag = language.command_tag_get( user_input );
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player typed: " << user_input << ", found ID: " << int( command_tag );
   return command_tag;
}

std::string UserInput::player_string_get()
{
   std::string player_string( "" );

   std::getline( std::cin, player_string );

   return player_string;
}
