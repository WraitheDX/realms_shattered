
#include "file_io.hpp"

#include <fstream>

#include "../platform/platform.hpp"

const bool FileIO::write_file( const std::string &file_contents, const std::string &file_name, const bool truncate_file )
{
   std::ios_base::openmode file_write_flag;
   if( truncate_file ) {
      file_write_flag = std::ios::trunc;
   } else {
      file_write_flag = std::ios::app;
   }
   
   // TODO (WraitheDX): Add generic call to abstracted platform-specific error checking for file_io calls
   std::string file_path = get_working_directory() + "/" + file_name;
   std::ofstream file( file_path, file_write_flag );
   if( !file.is_open() ) {
      return false;
   }

   // Write 'file_contents' to the file
   file << file_contents;

   file.close();

   return true;
}
