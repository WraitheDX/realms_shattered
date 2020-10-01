
#include "user_input.hpp"

#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

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
string UserInput::player_language_get( Console &console, Language &language){
   // all the available lanaguages need to be written in this array 
   std::string Languages = ["en"];
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Asking player for preferred language \n";
   static const int TEXT_ENTER_NAME_POSITION_Y( 1 );
   for (int i = 0 ; i < Languages.size(); i++)
      cout << i+1 <<" - "<< Languages[i] <<endl;
   bool check_lang = false;
   while( !check_lang ) {
      cout << "Write your preferred language \t\tplease be careful to write it with case sensitive ex: en \n";
      console.cursor_position_set( 0, TEXT_ENTER_NAME_POSITION_Y );
     
      std::string preferred_lang( "" );
      std::getline( std::cin, preferred_lang );
      for (int i = 0 ; i < Languages.size(); i++){
         if (preferred_lang == Languages[i])
            check_lang = true;
         break;
      }
      

      if( preferred_lang.empty() || check_lang == false) {
         std:: cout << " Invalid language. Please try again\n";
         continue;
      }
      return preferred_lang;      

   }
}

