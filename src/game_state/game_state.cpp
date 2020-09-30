
#include "game_state.hpp"

#include <iostream>

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
   m_console.title_set( m_game_title );

   m_language.commands_load( "data/language/en_commands.txt" );
   m_language.text_load( "data/language/en_game_text.txt" );

   // The game is now initialized and ready to begin the gameplay loop.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";
   
   print_dimensions_setup();
   player_name_get();
   return true;
}

void GameState::player_name_get()
{
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Asking player for name";

   static const int TEXT_ENTER_NAME_POSITION_Y( 1 );

   while( true ) {
      m_console.print( m_language.text_tag_get( "tag_name_entry"), 0, TEXT_ENTER_NAME_POSITION_Y );

      m_console.print( " > ", 0, TEXT_ENTER_NAME_POSITION_Y + 1 );
      std::string name( m_user_input.player_string_get() );

      m_console.clear();

      if( name.empty() ) {
         continue;
      }

      m_game_data.player_get()->name_set( name );
      Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player entered name: " << m_game_data.player_get()->name_get();
      break;
   }
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
      }
   }
}
