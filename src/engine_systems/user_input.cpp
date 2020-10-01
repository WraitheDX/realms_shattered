
#include "user_input.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "logger.hpp"
#include "../entities/actor.hpp"

const CommandTag UserInput::player_command_get( Language &language )
{
   std::string user_input( "" );
   // Getline allows us to read the entirety of the player's input, including spaces.
   std::getline( std::cin, user_input );

   CommandTag command_tag = language.command_tag_get( user_input );
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player typed: " << user_input << ", found ID: " << int( command_tag );
   return command_tag;
}

void UserInput::player_name_get( Console &console, GameData &game_data, Language &language )
{
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Asking player for name";

   static const int TEXT_ENTER_NAME_POSITION_Y( 1 );

   while( true ) {
      console.print( language.text_tag_get( "tag_name_entry"), 0, TEXT_ENTER_NAME_POSITION_Y );

      console.print( " > ", 0, TEXT_ENTER_NAME_POSITION_Y + 1 );
      std::string name( player_string_get() );

      console.clear();

      if( name.empty() ) {
         continue;
      }

      game_data.player_get()->name_set( name );
      Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player entered name: " << game_data.player_get()->name_get();
      break;
   }
}

std::string UserInput::player_language_get( Console &console, Language &language){
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Asking player for preferred language";

   // all the available lanaguages need to be written in this array 
   std::vector <std::string> language_vector;
   language_vector.push_back( std::string( "en" ) );

   const int TEXT_LANGUAGE_INSTRUCTION_POSITION_Y( console.height_get() - 4 );
   const int TEXT_LANGUAGE_ENTRY_POSITION_Y( TEXT_LANGUAGE_INSTRUCTION_POSITION_Y + 1 );
   const int TEXT_LANGUAGE_POSITION_Y( 1 );
   bool check_lang = false;
   while( !check_lang ) {
      for( int i = 0 ; i < language_vector.size(); i++ ) {
         console.print( language_vector[ i ], 2, TEXT_LANGUAGE_POSITION_Y + i );
      }

      console.print( "Write your preferred language (entry is case sensitive Ex: en)", 1, TEXT_LANGUAGE_INSTRUCTION_POSITION_Y );
      console.print( "> ", 0, TEXT_LANGUAGE_ENTRY_POSITION_Y );
     
      std::string preferred_lang( "" );
      std::getline( std::cin, preferred_lang );
      for( int i( 0 ); i < language_vector.size(); i++ ){
         if( preferred_lang == language_vector[ i ] ) {
            console.clear();
            return preferred_lang;
         }
      }
      
      console.print( "Invalid language, please try again." ), 1, TEXT_LANGUAGE_ENTRY_POSITION_Y + 1;
      console.pause();
      console.clear();
   }

   // If for any reason the while loop is escaped, we have an invalid language selection.
   return "INVALID";
}

std::string UserInput::player_string_get()
{
   std::string player_string( "" );

   std::getline( std::cin, player_string );

   return player_string;
}
