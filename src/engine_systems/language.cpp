
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
   std::map <std::string, std::string> command_map;
   if( !FileIO::file_tags_parse( command_map, file_name ) ) {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Language::commands_load() failed to parse tags from file: " << file_name;
      return false;
   }

   std::map <std::string, std::string>::iterator command_map_iter( command_map.begin() );
   std::map <std::string, std::string>::iterator command_map_end( command_map.end() );
   for( ; command_map_iter != command_map_end; ++command_map_iter ) {
      if( command_map_iter->first == "tag_command_accept" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_ACCEPT;
      } else if( command_map_iter->first == "tag_command_attack" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_ATTACK;
      } else if( command_map_iter->first == "tag_command_back" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_BACK;
      } else if( command_map_iter->first == "tag_command_help" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_HELP;
      } else if( command_map_iter->first == "tag_command_load" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_LOAD;
      } else if( command_map_iter->first == "tag_command_move" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_MOVE;
      } else if( command_map_iter->first == "tag_command_quit" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_QUIT;
      } else if( command_map_iter->first == "tag_command_rift" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_RIFT;
      } else if( command_map_iter->first == "tag_command_save" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_SAVE;
      } else if( command_map_iter->first == "tag_command_height" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_HEIGHT;
      } else if( command_map_iter->first == "tag_command_width" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_WIDTH;
      } else if( command_map_iter->first == "tag_command_offset_x" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_OFFSET_X;
      } else if( command_map_iter->first == "tag_command_offset_y" ) {
         commands_map[ command_map_iter->second ] = CommandTag::COMMAND_OFFSET_Y;
      }
   }

   return true;
}

const bool Language::text_load( const std::string &file_name )
{
   if( !FileIO::file_tags_parse( text_map, file_name ) ) {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Language::text_load() failed to parse tags from file: " << file_name;
      return false;
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
