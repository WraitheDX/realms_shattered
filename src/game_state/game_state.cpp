
#include "game_state.hpp"

#include <iostream>
#include <random>
#include <time.h>

#include "../engine_systems/file_io.hpp"
#include "../engine_systems/logger.hpp"
#include "../entities/actor.hpp"

GameState::GameState( const std::string &game_title ) :
   m_game_state_current( GameStateEnum::GAME_STATE_PLAYER_HUB ),
   m_game_title( game_title ),
   m_console(),
   m_game_data(),
   m_language(),
   m_user_input(),
   m_user_interface()
{

}

const bool GameState::initialize()
{
   srand( time( NULL ) );

   m_console.clear();
   m_console.title_set( m_game_title );

   ConfigFile config_file = FileIO::config_read();

   if( config_file.m_language == "INVALID" ) {
      config_file.m_language = m_user_input.player_language_get( m_console, m_language );

      FileIO::config_write( config_file );
   }

   // TODO (WraitheDX): Even though we should have a valid language set at this point, the language files
   // might be missing, so check for them before moving on.

   // Load the game and command text for the player's preferred language
   m_language.commands_load( "data/language/" + config_file.m_language + "_commands.txt" );
   m_language.text_load( "data/language/" + config_file.m_language + "_game_text.txt" );

   // If any of the game dimensions are invalid, have the user set their preferred dimensions
   if( config_file.m_game_height < m_console.m_print_height_min ||
       config_file.m_game_width < m_console.m_print_width_min ||
       config_file.m_game_offset_x < 0 ||
       config_file.m_game_offset_y < 0 ) {
      print_dimensions_setup();
      
      config_file.m_game_height = m_console.m_print_height;
      config_file.m_game_width = m_console.m_print_width;
      config_file.m_game_offset_x = m_console.m_print_offset_x;
      config_file.m_game_offset_y = m_console.m_print_offset_y;

      FileIO::config_write( config_file );
   }

   m_console.m_print_height = config_file.m_game_height;
   m_console.m_print_width = config_file.m_game_width;
   m_console.m_print_offset_x = config_file.m_game_offset_x;
   m_console.m_print_offset_y = config_file.m_game_offset_y;

   // This will eventually be in a new_game function or game_state
   // player_name_get();

   // The game is now initialized and ready to begin the gameplay loop.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";
   return true;
}
  
void GameState::print_dimensions_setup()
{
   int console_buffer_width( 0 );
   int console_buffer_height( 0 );
   m_console.buffer_dimensions_get( console_buffer_width, console_buffer_height );

   bool dimensions_setup_running( true );
   while( dimensions_setup_running ) {
      int console_width = m_console.width_get();
      int console_height = m_console.height_get();
      m_console.print_box( 0, 0, console_width, console_height, '+' );

      const std::string SETUP_TITLE( m_language.text_tag_get( "tag_console_dimensions_setup_title" ) );
      m_console.print( SETUP_TITLE, ( ( console_width / 2 ) - ( SETUP_TITLE.length() / 2 ) ), 2 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_instructions" ), 2, 4 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_note" ), 2, 5 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_width" ), 2, 7 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_height" ), 2, 8 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_xoffset" ), 2, 9 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_yoffset" ), 2, 10 );
      m_console.print( m_language.text_tag_get( "tag_console_dimensions_setup_accept" ), 2, 12 );

      m_console.print( m_language.text_tag_get( "tag_command" ) + ": ", 2, ( console_height - 2 ) );
      
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
      
      CommandTag command_tag( m_language.command_tag_get( command_string ) );
      
      switch( command_tag ) {
         case CommandTag::COMMAND_INVALID:
            break;
         case CommandTag::COMMAND_HEIGHT:
            m_console.printable_height_set( command_value );
            break;
         case CommandTag::COMMAND_WIDTH:
            m_console.printable_width_set( command_value );
            break;
         case CommandTag::COMMAND_OFFSET_X:
            m_console.printable_offset_x_set( command_value );
            break;
         case CommandTag::COMMAND_OFFSET_Y:
            m_console.printable_offset_y_set( command_value );
            break;
         case CommandTag::COMMAND_ACCEPT:
            // TODO (WraitheDX): Save print dimensions to config file
            dimensions_setup_running = false;
            break;
      }

      m_console.clear();
   }
}

void GameState::run()
{
   while( m_game_data.is_game_running() ) {
      switch( m_game_state_current ) {
         case GameStateEnum::GAME_STATE_DEV_MENU:
            game_state_dev_menu();
            break;
         case GameStateEnum::GAME_STATE_HELP:
            game_state_help();
            break;
         case GameStateEnum::GAME_STATE_LOAD:
            game_state_load();
            break;
         case GameStateEnum::GAME_STATE_MAIN_MENU:
            game_state_main_menu();
            break;
         case GameStateEnum::GAME_STATE_PLAYER_HUB:
            game_state_player_hub();
            break;
         case GameStateEnum::GAME_STATE_RIFT:
            game_state_rift();
            break;
      }
   }
}
