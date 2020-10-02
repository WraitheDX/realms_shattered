
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
   std::map <std::string, std::string> languages_supported;
   languages_supported[ "en" ] = "English";
 
   const std::map <std::string, std::string>::iterator languages_supported_end( languages_supported.end() );

   const std::string TITLE_STRING( "Language Selection" );
   const int TITLE_POSITION_X( ( console.width_get() / 2 ) - ( TITLE_STRING.length() / 2 ) );

   const int TEXT_LANGUAGE_INSTRUCTION_POSITION_Y( console.height_get() - 3 );
   const int TEXT_LANGUAGE_ENTRY_POSITION_Y( TEXT_LANGUAGE_INSTRUCTION_POSITION_Y + 1 );
   const int TEXT_LANGUAGE_POSITION_Y( 6 );

   while( true ) {
      console.print_box( 0, 0, console.width_get(), 5, '+' );
      console.print_box( 0, 0, console.width_get(), console.height_get(), '+' );
      console.print_box( 0, console.height_get() - 4, console.width_get(), 4, '+' );
      console.print( TITLE_STRING, TITLE_POSITION_X, 2 );
      
      int iteration_count( 0 );
      std::map <std::string, std::string>::iterator languages_supported_iterator( languages_supported.begin() );
      for( ; languages_supported_iterator != languages_supported_end; ++languages_supported_iterator ) {
         std::string language_line( "en - " + languages_supported_iterator->second );
         console.print( language_line, 5, TEXT_LANGUAGE_POSITION_Y + iteration_count );
         ++iteration_count;
      }

      console.print( "Please type the prefix of your preferred language...", 2, TEXT_LANGUAGE_INSTRUCTION_POSITION_Y );
      console.print( "> ", 2, TEXT_LANGUAGE_ENTRY_POSITION_Y );
     
      std::string preferred_lang( "" );
      std::getline( std::cin, preferred_lang );

      languages_supported_iterator = languages_supported.begin();
      for( ; languages_supported_iterator != languages_supported_end; ++languages_supported_iterator ){
         if( preferred_lang == languages_supported_iterator->first ) {
            console.clear();
            return preferred_lang;
         }
      }
      
      console.clear();
   }

   // If for any reason the while loop is escaped, default to English language
   return "en";
}

std::string UserInput::player_string_get()
{
   std::string player_string( "" );

   std::getline( std::cin, player_string );

   return player_string;
}
