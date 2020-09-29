
#include "language.hpp"

#include <iostream>
#include <vector>

#include "file_io.hpp"
#include "logger.hpp"

const bool Language::commands_load( const std::string &file_name )
{
   std::vector <std::string> file_contents;
   if( !FileIO::file_read( file_contents, file_name ) ) {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Language::commands_load() failed to load contents of: " << file_name;
      return false;
   }

   const int FILE_CONTENTS_SIZE( file_contents.size() );
   for( int iterator = 0; iterator < FILE_CONTENTS_SIZE; ++iterator ) {
      std::string file_line_current( file_contents[ iterator ] );
      if( file_line_current.empty() ) {
         continue;
      } else if( file_line_current.find( "tag_command_quit" ) != std::string::npos ) {
         int string_found_position( file_line_current.find( ":" ) );
         std::string command_value( file_line_current.substr( 0, string_found_position ) );
         std::string command_key( file_line_current.substr( string_found_position, std::string::npos ) );

         for( int command_key_iterator( 0 ); command_key_iterator < command_key.size(); ++command_key_iterator ) {
            if( command_key[ command_key_iterator ] == ' '  || command_key[ command_key_iterator ] == ':' ) {
               command_key.erase( command_key.begin() + command_key_iterator );
               --command_key_iterator;
            }
         }

         for( int command_value_iterator( 0 ); command_value_iterator < command_value.size(); ++command_value_iterator ) {
            if( command_value[ command_value_iterator ] == ' '  || command_value[ command_value_iterator ] == ':' ) {
               command_value.erase( command_value.begin() + command_value_iterator );
               --command_value_iterator;
            }
         }

         commands_map[ command_key ] = command_value;
      }
   }

   return true;
}

const CommandTag Language::command_tag_get( const std::string &player_input )
{
   std::string command_tag_string( "" );
   std::map <std::string, std::string>::iterator commands_map_iter( commands_map.begin() );
   std::map <std::string, std::string>::iterator commands_map_end( commands_map.end() );
   for( ; commands_map_iter != commands_map_end; ++commands_map_iter ) {
      if( commands_map_iter->first == player_input ) {
         command_tag_string = commands_map_iter->second;
         break;
      }
   }

   if( commands_map_iter == commands_map_end ) {
      return CommandTag::COMMAND_INVALID;
   } else if( command_tag_string == "tag_command_quit" ) {
      return CommandTag::COMMAND_QUIT;
   }

   return CommandTag::COMMAND_INVALID;
}
