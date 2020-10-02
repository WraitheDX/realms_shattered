
#include "file_io.hpp"

#include <fstream>

#include "../entities/actor.hpp"
#include "../platform/platform.hpp"
  
const ConfigFile FileIO::config_read()
{
   ConfigFile config_file;

   std::map <std::string, std::string> file_contents;
   if( !file_tags_parse( file_contents, "config.txt" ) ) {
      return config_file;
   }

   std::map <std::string, std::string>::iterator file_contents_iterator( file_contents.begin() );
   std::map <std::string, std::string>::iterator file_contents_end( file_contents.end() );
   for( ; file_contents_iterator != file_contents_end; ++file_contents_iterator ) {
      if( file_contents_iterator->first == "language" ) {
         config_file.m_language = file_contents_iterator->second;
      } else if( file_contents_iterator->first == "width" ) {
         if( isdigit( file_contents_iterator->second[ 0 ] ) ) {
            config_file.m_game_width = atoi( file_contents_iterator->second.c_str() );
         }
      } else if( file_contents_iterator->first == "height" ) {
         if( isdigit( file_contents_iterator->second[ 0 ] ) ) {
            config_file.m_game_height = atoi( file_contents_iterator->second.c_str() );
         }
      } else if( file_contents_iterator->first == "xoffset" ) {
         if( isdigit( file_contents_iterator->second[ 0 ] ) ) {
            config_file.m_game_offset_x = atoi( file_contents_iterator->second.c_str() );
         }
      } else if( file_contents_iterator->first == "yoffset" ) {
         if( isdigit( file_contents_iterator->second[ 0 ] ) ) {
            config_file.m_game_offset_y = atoi( file_contents_iterator->second.c_str() );
         }
      }
   }

   return config_file;
}

void FileIO::config_write( const ConfigFile &config_file )
{
   std::vector <std::string> file_contents;
   file_contents.push_back( "" );
   file_contents.push_back( "language:" + config_file.m_language );
   file_contents.push_back( "" );
   file_contents.push_back( "width:" + std::to_string( config_file.m_game_width ) );
   file_contents.push_back( "height:" + std::to_string( config_file.m_game_height ) );
   file_contents.push_back( "xoffset:" + std::to_string( config_file.m_game_offset_x ) );
   file_contents.push_back( "yoffset:" + std::to_string( config_file.m_game_offset_y ) );
   file_contents.push_back( "" );

   file_write( file_contents, "config.txt", true );
}

const bool FileIO::file_read( std::vector <std::string> &file_contents, const std::string &file_name )
{
   std::string file_path = working_directory_get() + "/" + file_name;
   std::ifstream file( file_path );
   if( !file.is_open() ) {
      return false;
   }

   while( !file.eof() ) {
      std::string file_line( "" );
      std::getline( file, file_line );
      file_contents.push_back( file_line );
   }

   file.close();

   return true;
}

const bool FileIO::file_tags_parse( std::map <std::string, std::string> &parsed_tags, const std::string &file_name )
{
   std::vector <std::string> file_contents;
   if( !file_read( file_contents, file_name ) ) {
      return false;
   }

   std::vector <std::string>::iterator file_contents_iterator( file_contents.begin() );
   std::vector <std::string>::iterator file_contents_end( file_contents.end() );
   for( ; file_contents_iterator != file_contents_end; ++file_contents_iterator ) {
      const int tag_separator_position( (*file_contents_iterator).find( ":" ) );

      // If a tag separator (:) cannot be found, skip this line
      if( tag_separator_position == std::string::npos ) {
         continue;
      }

      std::string key_string( (*file_contents_iterator).substr( 0, tag_separator_position ) );
      std::string value_string( (*file_contents_iterator).substr( tag_separator_position + 1, std::string::npos ) );

      parsed_tags[ key_string ] = value_string;
   }

   return true;
}

const bool FileIO::file_write( const std::string &file_contents, const std::string &file_name, const bool truncate_file )
{
   std::ios_base::openmode file_write_flag;
   if( truncate_file ) {
      file_write_flag = std::ios::trunc;
   } else {
      file_write_flag = std::ios::app;
   }
   
   std::string file_path = working_directory_get() + "/" + file_name;
   std::ofstream file( file_path, file_write_flag );
   if( !file.is_open() ) {
      return false;
   }

   // Write 'file_contents' to the file
   file << file_contents;

   file.close();

   return true;
}

const bool FileIO::file_write( const std::vector <std::string> &file_contents, const std::string &file_name, const bool truncate_file )
{
   std::ios_base::openmode file_write_flag;
   if( truncate_file ) {
      file_write_flag = std::ios::trunc;
   } else {
      file_write_flag = std::ios::app;
   }
   
   std::string file_path = working_directory_get() + "/" + file_name;
   std::ofstream file( file_path, file_write_flag );
   if( !file.is_open() ) {
      return false;
   }

   // Write 'file_contents' to the file
   const int FILE_CONTENTS_SIZE( file_contents.size() );
   for( int file_contents_iterator( 0 ); file_contents_iterator < FILE_CONTENTS_SIZE; ++file_contents_iterator ) {
      file << file_contents[ file_contents_iterator ] + "\n";
   }

   file.close();

   return true;
}

const bool FileIO::player_files_find( std::vector<std::string> & dir_content )
{   
   return get_file_list( dir_content, working_directory_get() + "/save\\*" );
}

const bool FileIO::player_file_load( std::vector <std::string> &dir_content, const std::string &file_name )
{
   std::string file_path = working_directory_get() + "/save/" + file_name;
   std::ifstream file( file_path );

   if (!file.is_open()){
      return false;
   } else {
      while( !file.eof() ) {
         std::string file_line( "" );
         std::getline( file, file_line );
         dir_content.push_back( file_line );
      }
   }

   return true;
}

const bool FileIO::player_file_save( GameData &game_data ) {
   
   // Check if save folder exists

   std::vector <std::string> file_contents;
   file_contents.push_back( "name:" + game_data.player_get()->name_get() );
   file_contents.push_back( "health_current:" + std::to_string( game_data.player_get()-> health_current_get() ) );
   file_contents.push_back( "health_max:" + std::to_string ( game_data.player_get()->health_max_get() ) );

   file_write( file_contents, "save/" + game_data.player_get()->name_get() + ".txt", true );

   return true;
}