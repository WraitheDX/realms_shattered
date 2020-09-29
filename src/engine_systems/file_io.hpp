
#ifndef _FILE_IO_HPP_
#define _FILE_IO_HPP_

#include <string>
#include <vector>

/*
   Class container for static file reading and writing functions.
*/
class FileIO {
public:
   /*
      Reads a file as a vector of strings, filling the 'file_contents' parameter with the contents of the file.
   */
   static const bool file_read( std::vector <std::string> &file_contents, const std::string &file_name );

   /*
      Writes a single string to the specified file name (obtains working directory internally), and requires truncation flag.
   */
   static const bool file_write( const std::string &file_contents, const std::string &file_name, const bool truncate_file );
};

#endif // _FILE_IO_HPP_
