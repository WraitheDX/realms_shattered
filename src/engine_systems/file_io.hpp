
#ifndef _FILE_IO_HPP_
#define _FILE_IO_HPP_

#include <string>

/*
   Class container for static file reading and writing functions.
*/
class FileIO {
public:
   /*
      Writes a single string to the specified file name (obtains working directory internally), and requires truncation flag.
   */
   static const bool write_file( const std::string &file_contents, const std::string &file_name, const bool truncate_file );
};

#endif // _FILE_IO_HPP_
