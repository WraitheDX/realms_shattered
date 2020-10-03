
#include "user_input.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "config_file.hpp"
#include "file_io.hpp"
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

std::vector <std::string> UserInput::player_input_break( std::string &player_input )
{
   std::vector <std::string> player_input_broken;
   while( !player_input.empty() ) {
      int space_position( player_input.find( " " ) );
      if( space_position == std::string::npos ) {
         player_input_broken.push_back( player_input );
         player_input.clear();
      } else {
         player_input_broken.push_back( player_input.substr( 0, space_position ) );
         player_input.erase( 0, space_position + 1 );
      }
   }

   return player_input_broken;
}

const bool UserInput::player_input_is_number( int &player_number, std::string &player_input )
{
   for( int iterator( 0 ); iterator < player_input.size(); ++iterator ) {
      if( !isdigit( player_input[ iterator ] ) ) {
         return false;
      }
   }

   player_number = atoi( player_input.c_str() );
   return true;
}

std::string UserInput::player_input_process( std::vector <CommandTag> &command_tags, Language &language )
{
   std::string user_input( "" );
   // Getline allows us to read the entirety of the player's input, including spaces.
   std::getline( std::cin, user_input );
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player typed: " << user_input;

   std::vector <std::string> user_input_broken( player_input_break( user_input ) );
   std::string input_remainder( "" );
   for( int iterator( 0 ); iterator < user_input_broken.size(); ++iterator ) {
      CommandTag command_tag_found = language.command_tag_get( user_input_broken[ iterator ] );
      if( command_tag_found == CommandTag::COMMAND_INVALID ) {
         if( !input_remainder.empty() ) {
            input_remainder.append( " " );
         }

         input_remainder.append( user_input_broken[ iterator ] );
      } else {
         command_tags.push_back( command_tag_found );
      }
   }

   return input_remainder;
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
  
void UserInput::print_dimensions_setup( Console &console, Language &language )
{
   const std::string SETUP_TITLE( language.text_tag_get( "tag_console_dimensions_setup_title" ) );

   const int INSTRUCTIONS_POSITION_Y( 6 );

   bool dimensions_setup_running( true );
   while( dimensions_setup_running ) {
      int console_buffer_width( 0 );
      int console_buffer_height( 0 );
      console.buffer_dimensions_get( console_buffer_width, console_buffer_height );

      int console_width = console.width_get();
      int console_height = console.height_get();
      console.print_box( 0, 0, console_width, console_height, '+' );
      console.print_box( 0, 0, console_width, 5, '+' );
      console.print_box( 0, console_height - 3, console_width, 3, '+' );

      console.print( SETUP_TITLE, ( ( console_width / 2 ) - ( SETUP_TITLE.length() / 2 ) ), 2 );
      console.print( language.text_tag_get( "tag_console_dimensions_setup_instructions" ), 2, INSTRUCTIONS_POSITION_Y );
      console.print( language.text_tag_get( "tag_console_dimensions_setup_note" ), 2, INSTRUCTIONS_POSITION_Y + 1 );

      console.print( language.text_tag_get( "tag_console_dimensions_setup_width" ), 2, INSTRUCTIONS_POSITION_Y + 3 );
      console.print( language.text_tag_get( "tag_console_dimensions_setup_height" ), 2, INSTRUCTIONS_POSITION_Y + 4 );
      console.print( language.text_tag_get( "tag_console_dimensions_setup_xoffset" ), 2, INSTRUCTIONS_POSITION_Y + 5 );
      console.print( language.text_tag_get( "tag_console_dimensions_setup_yoffset" ), 2, INSTRUCTIONS_POSITION_Y + 6 );

      console.print( language.text_tag_get( "tag_console_dimensions_setup_accept" ), 2, INSTRUCTIONS_POSITION_Y + 8 );

      console.print( language.text_tag_get( "tag_command" ) + ": ", 2, ( console_height - 2 ) );
      
      std::string player_input( "" );
      std::getline( std::cin, player_input );
      while( !player_input.empty() && player_input[ 0 ] == ' ' ) {
         player_input.erase( player_input.begin() );
      }
      
      std::string command_string( player_input );
      int command_value( 0 );
      int position_of_space_character( player_input.find( ' ' ) );
      if( position_of_space_character != std::string::npos ) {
         command_string = player_input.substr( 0, position_of_space_character );
         
         std::string value_string = player_input.substr( position_of_space_character + 1, std::string::npos );
         bool is_value( false );
         for( int iterator( 0 ); iterator < value_string.size(); ++iterator ) {
            if( std::isdigit( value_string[ iterator ] ) ) {
               is_value = true;
               break;
            }
         }

         if( is_value ) {
            command_value = atoi( value_string.c_str() );
         }
      }
      
      CommandTag command_tag( language.command_tag_get( command_string ) );
      
      switch( command_tag ) {
         case CommandTag::COMMAND_INVALID:
            break;
         case CommandTag::COMMAND_HEIGHT:
            console.printable_height_set( command_value );
            break;
         case CommandTag::COMMAND_WIDTH:
            console.printable_width_set( command_value );
            break;
         case CommandTag::COMMAND_OFFSET_X:
            console.printable_offset_x_set( command_value );
            break;
         case CommandTag::COMMAND_OFFSET_Y:
            console.printable_offset_y_set( command_value );
            break;
         case CommandTag::COMMAND_ACCEPT:
            dimensions_setup_running = false;
            break;
      }

      console.clear();
   }
}

void UserInput::settings_menu( Console &console, Language &language )
{
   console.clear();

   const std::string TITLE_STRING( language.text_tag_get( "tag_settings_title" ) );
   const int INSTRUCTIONS_POSITION_Y( 6 );
   ConfigFile config_file( FileIO::config_read() );

   bool settings_menu_running( true );
   while( settings_menu_running ) {
      int console_buffer_width( 0 );
      int console_buffer_height( 0 );
      console.buffer_dimensions_get( console_buffer_width, console_buffer_height );

      int console_width = console.width_get();
      int console_height = console.height_get();
      console.print_box( 0, 0, console_width, console_height, '+' );
      console.print_box( 0, 0, console_width, 5, '+' );
      console.print_box( 0, console_height - 3, console_width, 3, '+' );

      console.print( TITLE_STRING, ( ( console_width / 2 ) - ( TITLE_STRING.length() / 2 ) ), 2 );
      console.print( language.text_tag_get( "tag_settings_display" ), 2, INSTRUCTIONS_POSITION_Y );
      console.print( language.text_tag_get( "tag_settings_language" ), 2, INSTRUCTIONS_POSITION_Y + 1 );

      console.print( language.text_tag_get( "tag_command" ) + ": ", 2, ( console_height - 2 ) );
      CommandTag command_tag( player_command_get( language ) );
      
      switch( command_tag ) {
         case CommandTag::COMMAND_INVALID:
            break;
         case CommandTag::COMMAND_DISPLAY:
            console.clear();
            UserInput::print_dimensions_setup( console, language );
      
            config_file.m_game_height = console.height_get();
            config_file.m_game_width = console.width_get();
            config_file.m_game_offset_x = console.m_print_offset_x;
            config_file.m_game_offset_y = console.m_print_offset_y;
            
            FileIO::config_write( config_file );
            break;
         case CommandTag::COMMAND_LANGUAGE:
            console.clear();
            config_file.m_language = UserInput::player_language_get( console, language );
            FileIO::config_write( config_file );
            break;
         case CommandTag::COMMAND_BACK:
            settings_menu_running = false;
            break;
      }

      console.clear();
   }
}
