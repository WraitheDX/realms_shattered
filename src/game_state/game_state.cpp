
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
   m_action_log(),
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
      m_user_input.print_dimensions_setup( m_console, m_language );
      
      config_file.m_game_height = m_console.height_get();
      config_file.m_game_width = m_console.width_get();
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


