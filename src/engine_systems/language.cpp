
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
      std::string command_key( "" );
      std::string command_value( "" );

      if( file_line_current.empty() ) {
         continue;
      } else {
         if( key_value_pair_get( file_line_current, command_key, command_value ) ) {
            if( command_key == "tag_command_quit" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_QUIT;
            } else if( command_key == "tag_command_help" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_HELP;
            }
         }
      }
   }

   return true;
}

const CommandTag Language::command_tag_get( const std::string &player_input )
{
   std::string command_tag_string( "" );
   std::map <std::string, CommandTag>::iterator commands_map_iter( commands_map.begin() );
   std::map <std::string, CommandTag>::iterator commands_map_end( commands_map.end() );
   for( ; commands_map_iter != commands_map_end; ++commands_map_iter ) {
      if( commands_map_iter->first == player_input ) {
         return commands_map_iter->second;
      }
   }

   return CommandTag::COMMAND_INVALID;
}

const bool Language::key_value_pair_get( const std::string &line, std::string &key, std::string &value )
{
   int string_found_position( line.find( ":" ) );
   key = line.substr( 0, string_found_position );
   value = line.substr( string_found_position, std::string::npos );

   for( int key_iterator( 0 ); key_iterator < key.size(); ++key_iterator ) {
      if( key[ key_iterator ] == ' ' || key[ key_iterator ] == ':' ) {
         key.erase( key.begin() + key_iterator );
         --key_iterator;
      }
   }

   for( int value_iterator( 0 ); value_iterator < value.size(); ++value_iterator ) {
      if( value[ value_iterator ] == ' ' || value[ value_iterator ] == ':' ) {
         value.erase( value.begin() + value_iterator );
         --value_iterator;
      }
   }

   if( key.empty() || value.empty() ) {
      return false;
   }

   return true;
}
