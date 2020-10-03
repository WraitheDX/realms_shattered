
#include "game_state.hpp"

#include "../engine_systems/file_io.hpp"
#include "../engine_systems/logger.hpp"
#include "../entities/actor.hpp"

void GameState::game_state_player_hub()
{
   m_console.print_box( 0, 0, m_console.width_get(), m_console.height_get(), '+' );
   m_console.print( m_game_title, ( ( m_console.width_get() / 2 ) - ( m_game_title.length() / 2 ) ), 1 );

   m_user_interface.player_stats_brief_display( m_console, m_language, m_game_data );
   m_user_interface.action_log_display( m_action_log, m_console );
   m_user_interface.command_prompt_display( m_console, m_language );
   CommandTag command_tag( m_user_input.player_command_get( m_language ) );
      
   switch( command_tag ) {
      case CommandTag::COMMAND_INVALID:
         break;
      case CommandTag::COMMAND_RIFT:
         Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player entered a rift";
         m_game_data.rift_create();
         m_action_log.add_line( m_game_data.player_get()->name_get() + " has entered a rift." );
         m_game_state_current = GameStateEnum::GAME_STATE_RIFT;
         break;
      case CommandTag::COMMAND_LOAD:
         m_game_state_current = GameStateEnum::GAME_STATE_LOAD;
         break;
      case CommandTag::COMMAND_SAVE:
         FileIO::player_file_save( m_action_log, m_game_data );
         break;
      case CommandTag::COMMAND_SETTINGS:
         m_user_input.settings_menu( m_console, m_language );
         break;
      case CommandTag::COMMAND_HELP:
         m_game_state_current = GameStateEnum::GAME_STATE_HELP;
         break;
      case CommandTag::COMMAND_QUIT:
         m_game_data.game_terminate();
         break;
   }
      
   m_console.clear();
}
