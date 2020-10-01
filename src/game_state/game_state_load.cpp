
#include "game_state.hpp"

#include "../engine_systems/file_io.hpp"

void GameState::game_state_load()
{
   std::vector <std::string> saved_files;
   // read all the files in the save directory
   bool found_save_folder( FileIO::save_files_find( saved_files ) );
   if( !found_save_folder ) {
      m_console.print( "No save files found", 2, 2);
      return;
   }

   m_console.print("Your saved files are \t\t", 2, 2);
   for ( int file_iterator( 0 ); file_iterator < saved_files.size(); ++file_iterator ){
      m_console.print( saved_files[ file_iterator ], 5, ( 3 + file_iterator ) );
   }

   m_console.print( "Please type the exact name of the game you want to load \n", 2, 10 );
   m_user_interface.command_prompt_display( m_console, m_language );
   std::string player_input( m_user_input.player_string_get() );
   CommandTag command_tag( m_language.command_tag_get( player_input ) );
   std::vector <std::string> file_content;
      
   switch( command_tag ) {
      case CommandTag::COMMAND_INVALID:
         if( !FileIO::player_file_load( file_content, player_input ) ) {
            m_console.print( "Sorry, Could not find this file.", 2, 13 );
         }

         break;
      case CommandTag::COMMAND_QUIT:
         m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
         break;
   }
   
   m_console.pause();
   m_console.clear();
}
