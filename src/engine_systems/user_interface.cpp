
#include "user_interface.hpp"

#include <string>
#include <vector>

#include "../entities/actor.hpp"

void UserInterface::action_log_display( ActionLog &action_log, Console &console )
{
   int log_line_display_size( action_log.display_size_get() );
   int log_display_position_y( console.height_get() - log_line_display_size - 1 );

   console.print_box( 0, log_display_position_y - 1, console.width_get(), log_line_display_size + 2, '+' );

   std::vector <std::string> log_lines( action_log.log_lines_get() );
   int current_line_count( 0 );
   for( int iterator( log_lines.size() ); iterator > 0; --iterator ) {
      console.print( log_lines[ iterator - 1 ], 2, log_display_position_y + current_line_count );
      ++current_line_count;
      if( current_line_count >= log_line_display_size ) {
         return;
      }
   }
}

void UserInterface::command_prompt_display( Console &console, Language &language )
{
   static const int COMMAND_TEXT_POSITION_Y = console.height_get() - 9;
   
   console.print( language.text_tag_get( "tag_help_command_hint" ), 2, COMMAND_TEXT_POSITION_Y );
   console.print( language.text_tag_get( "tag_command" ) + ": ", 2, COMMAND_TEXT_POSITION_Y + 1 );
}

void UserInterface::help_list_display( Console &console, Language &language )
{
   static const int HELP_TEXT_POSITION_Y = 5;

   console.print( language.text_tag_get( "tag_help_command_list" ), 2, HELP_TEXT_POSITION_Y );
   console.print( language.text_tag_get( "tag_help_command_list_note" ), 2, HELP_TEXT_POSITION_Y + 1 );
   console.print( language.text_tag_get( "tag_help_command_list_quit" ), 2, HELP_TEXT_POSITION_Y + 3 );
}

// TODO (WraitheDX): Need to pause using something like cin, and display a language-specific pause message."
void UserInterface::pause_and_display_message( Console &console )
{
   static const int PAUSE_TEXT_POSITION_Y = 22;
   console.cursor_position_set( 0, PAUSE_TEXT_POSITION_Y );
   console.pause();
}

/*
   NOTE: Passing in GameData by value instead of reference will cause the retreived player pointer to lose its reference,
   which will cause the game to crash the next time the player's name is requested.
*/
void UserInterface::player_stats_brief_display( Console &console, Language &language, GameData &game_data )
{
   static const int PLAYER_TEXT_POSITION_Y = 1;

   Actor *player = game_data.player_get();
   console.print( "Name: " + player->name_get(), 2, PLAYER_TEXT_POSITION_Y );
   console.print( "Health: " + std::to_string( player->health_current_get() ) + "/" + std::to_string( player->health_max_get() ), 2, PLAYER_TEXT_POSITION_Y + 1 );
}
