
#include "game_state.hpp"

#include <iostream>

#include "../engine_systems/logger.hpp"

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

   m_user_input.player_name_get( m_console, m_language, m_game_data );
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
      }
   }
}
