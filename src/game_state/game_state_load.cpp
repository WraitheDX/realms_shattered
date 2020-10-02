
#include "game_state.hpp"

#include "../engine_systems/file_io.hpp"
#include "../engine_systems/logger.hpp"

void GameState::game_state_load()
{
   m_console.print_box( 0, 0, m_console.width_get(), m_console.height_get(), '+' );

   std::vector <std::string> saved_files;
   // read all the files in the save directory
   bool found_save_folder( FileIO::player_files_find( saved_files ) );
   if( !found_save_folder ) {
      m_console.print( "No save files found", 2, 8 );
   } else {
      m_console.print("Your saved files are \t\t", 2, 2);
      for ( int file_iterator( 0 ); file_iterator < saved_files.size(); ++file_iterator ){
         std::string file_name( saved_files[ file_iterator ] );
         m_console.print( file_name.substr( 0, file_name.length() - 4 ), 5, ( 3 + file_iterator ) );
      }
      
      m_console.print( "Please type quit to leave this menu", 2, 9 );
      m_console.print( "Please type the exact name of the game you want to load \n", 2, 10 );
   }

   m_user_interface.command_prompt_display( m_console, m_language );
   std::string player_input( m_user_input.player_string_get() );
   CommandTag command_tag( m_language.command_tag_get( player_input ) );
   std::vector <std::string> file_content;
      
   switch( command_tag ) {
      case CommandTag::COMMAND_INVALID: {
         bool file_found( false );
         for( int iterator( 0 ); iterator < saved_files.size(); ++iterator ) {
            if( player_input + ".txt" == saved_files[ iterator ] ) {
               if( FileIO::player_file_load( m_game_data, saved_files[ iterator ] ) ) {
                  file_found = true;
                  break;
               } else {
                  Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Failed to load found player file: " << saved_files[ iterator ];
               }
            }
         }

         if( !file_found ) {
            m_console.print( "Sorry, could not read the file.", 2, 13 );
         } else {
            m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
         }

         break;
      }
      case CommandTag::COMMAND_BACK:
         m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
         break;
      case CommandTag::COMMAND_QUIT:
         m_game_data.game_terminate();
         break;
   }
   
   m_console.clear();
}
