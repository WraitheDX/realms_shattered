
#include "game_state.hpp"

#include "../engine_systems/logger.hpp"

void GameState::game_state_help()
{
   const int HELP_TEXT_POSITION_Y = 6;
   const std::string TITLE_STRING( "Help Menu" );

   m_console.print_box( 0, 0, m_console.width_get(), m_console.height_get(), '+' );
   m_console.print_box( 0, 0, m_console.width_get(), 5, '+' );
   m_console.print_box( 0, m_console.height_get() - 3, m_console.width_get(), 3, '+' );

   m_console.print( TITLE_STRING, ( ( m_console.width_get() / 2 ) - ( TITLE_STRING.length() / 2 ) ), 2 );

   m_console.print( m_language.text_tag_get( "tag_help_command_list" ), 2, HELP_TEXT_POSITION_Y );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_note" ), 2, HELP_TEXT_POSITION_Y + 1 );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_move" ), 2, HELP_TEXT_POSITION_Y + 3 );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_attack" ), 2, HELP_TEXT_POSITION_Y + 4 );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_rift" ), 2, HELP_TEXT_POSITION_Y + 5 );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_settings" ), 2, HELP_TEXT_POSITION_Y + 6 );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_back" ), 2, HELP_TEXT_POSITION_Y + 7 );
   m_console.print( m_language.text_tag_get( "tag_help_command_list_quit" ), 2, HELP_TEXT_POSITION_Y + 8 );

   m_console.print( "Command: ", 2, m_console.height_get() - 2 );
   CommandTag command_tag( m_user_input.player_command_get( m_language ) );
      
   switch( command_tag ) {
      case CommandTag::COMMAND_INVALID:
         break;
      case CommandTag::COMMAND_BACK:
         m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
         break;
      case CommandTag::COMMAND_QUIT:
         m_game_data.game_terminate();
         break;
   }
      
   m_console.clear();
}
