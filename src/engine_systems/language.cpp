
#include "language.hpp"

#include <iostream>
#include <vector>

#include "file_io.hpp"
#include "logger.hpp"

/*
   TODO (WraitheDX): Expand upon the parsing of the language files. At the moment they do not handle leading or trailing spaces,
   so the files must conform exactly to the expected input.
*/

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
            if( command_key == "tag_command_accept" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_ACCEPT;
            } else if( command_key == "tag_command_help" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_HELP;
            } else if( command_key == "tag_command_move" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_MOVE;
            } else if( command_key == "tag_command_quit" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_QUIT;
            } else if( command_key == "tag_command_rift" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_RIFT;
            } else if( command_key == "tag_command_height" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_HEIGHT;
            } else if( command_key == "tag_command_width" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_WIDTH;
            } else if( command_key == "tag_command_offset_x" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_OFFSET_X;
            } else if( command_key == "tag_command_offset_y" ) {
               commands_map[ command_value ] = CommandTag::COMMAND_OFFSET_Y;
            }
         }
      }
   }

   return true;
}

const bool Language::text_load( const std::string &file_name )
{
   std::vector <std::string> file_contents;
   if( !FileIO::file_read( file_contents, file_name ) ) {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Language::text_load() failed to load contents of: " << file_name;
      return false;
   }

   const int FILE_CONTENTS_SIZE( file_contents.size() );
   for( int iterator = 0; iterator < FILE_CONTENTS_SIZE; ++iterator ) {
      std::string file_line_current( file_contents[ iterator ] );
      std::string text_key( "" );
      std::string text_value( "" );

      if( file_line_current.empty() ) {
         continue;
      } else {
         if( key_value_pair_get( file_line_current, text_key, text_value ) ) {
            text_map[ text_key ] = text_value;
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

const std::string Language::text_tag_get( const std::string &text_tag )
{
   std::map <std::string, std::string>::iterator text_map_iter( text_map.begin() );
   std::map <std::string, std::string>::iterator text_map_end( text_map.end() );
   for( ; text_map_iter != text_map_end; ++text_map_iter ) {
      if( text_map_iter->first == text_tag ) {
         return text_map_iter->second;
      }
   }

   return std::string( "TextTag: " + text_tag + " not found in the language map." );
}

const bool Language::key_value_pair_get( const std::string &line, std::string &key, std::string &value )
{
   int string_found_position( line.find( ":" ) );
   key = line.substr( 0, string_found_position );
   value = line.substr( string_found_position + 1, std::string::npos );

   if( key.empty() || value.empty() ) {
      return false;
   }

   return true;
}
