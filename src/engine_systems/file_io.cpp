
#include "file_io.hpp"

#include <fstream>

#include "../platform/platform.hpp"

// TODO (WraitheDX): Add generic call to abstracted platform-specific error checking for file_io calls
  
const ConfigFile FileIO::config_read()
{
   ConfigFile config_file;

   std::vector <std::string> file_contents;
   if( !file_read( file_contents, "config.txt" ) ) {
      return config_file;
   }

   std::vector <std::string>::iterator file_contents_iterator( file_contents.begin() );
   const std::vector <std::string>::iterator file_contents_end( file_contents.end() );
   for( ; file_contents_iterator != file_contents_end; ++file_contents_iterator ) {
      if( (*file_contents_iterator).find( "language" ) != std::string::npos ) {
         const int substring_position( (*file_contents_iterator).find( ":" ) );
         if( substring_position != std::string::npos ) {
            config_file.m_language = (*file_contents_iterator).substr( substring_position + 1, std::string::npos );
         }
      } else if( (*file_contents_iterator).find( "width" ) != std::string::npos ) {
         const int substring_position( (*file_contents_iterator).find( ":" ) );
         if( substring_position != std::string::npos ) {
            std::string value_string( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ) );
            if( isdigit( value_string[ 0 ] ) ) {
               config_file.m_game_width = atoi( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ).c_str() );
            }
         }
      } else if( (*file_contents_iterator).find( "height" ) != std::string::npos ) {
         const int substring_position( (*file_contents_iterator).find( ":" ) );
         if( substring_position != std::string::npos ) {
            std::string value_string( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ) );
            if( isdigit( value_string[ 0 ] ) ) {
               config_file.m_game_height = atoi( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ).c_str() );
            }
         }
      } else if( (*file_contents_iterator).find( "xoffset" ) != std::string::npos ) {
         const int substring_position( (*file_contents_iterator).find( ":" ) );
         if( substring_position != std::string::npos ) {
            std::string value_string( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ) );
            if( isdigit( value_string[ 0 ] ) ) {
               config_file.m_game_offset_x = atoi( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ).c_str() );
            }
         }
      } else if( (*file_contents_iterator).find( "yoffset" ) != std::string::npos ) {
         const int substring_position( (*file_contents_iterator).find( ":" ) );
         if( substring_position != std::string::npos ) {
            std::string value_string( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ) );
            if( isdigit( value_string[ 0 ] ) ) {
               config_file.m_game_offset_y = atoi( (*file_contents_iterator).substr( substring_position + 1, std::string::npos ).c_str() );
            }
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

const bool FileIO::save_files_find( const std::vector<std::string> & dir_content )
{
   /*
   DIR * dir = opendir ("/save");
   struct dirent *entry;
   if (dir == NULL)
      return false;
   else   
   {
      std::string filename;
      while( (entry = readdir(dir) ) != NULL){
         filename = entry->d_name;
         saved_files.push_back(filename.substr(0,filename.size()-4));
      }
   }

   closedir(dir);
   */

   return true;
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
         std::getline(file, file_line);
         dir_content.push_back(file_line);
      }
   }

   return true;
}