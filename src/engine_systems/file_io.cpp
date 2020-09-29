
#include "file_io.hpp"

#include <fstream>

#include "../platform/platform.hpp"

// TODO (WraitheDX): Add generic call to abstracted platform-specific error checking for file_io calls

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
