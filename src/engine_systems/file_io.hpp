
#ifndef _FILE_IO_HPP_
#define _FILE_IO_HPP_

#include <string>
#include <vector>

struct ConfigFile {
   ConfigFile():
      m_language( "en" ),
      m_game_width( 0 ),
      m_game_height( 0 ),
      m_game_offset_x( 0 ),
      m_game_offset_y( 0 )
   {
   
   }
   std::string m_language;

   int m_game_width;
   int m_game_height;
   int m_game_offset_x;
   int m_game_offset_y;
};

/*
   Class container for static file reading and writing functions.
*/
class FileIO {
public:
   /*
   *  Read in the configuration file and return a ConfigFile struct with all of the values.
   * 
   *  Creates, saves and returns a new config file if one could not be found.
   */
   static const ConfigFile config_read();

   /*
   *  Write the configuration file out to the root game folder.
   */
   static void config_write( const ConfigFile &config_file );
   
   /*
      Reads a file as a vector of strings, filling the 'file_contents' parameter with the contents of the file.
   */
   static const bool file_read( std::vector <std::string> &file_contents, const std::string &file_name );

   /*
      Writes a single string to the specified file name (obtains working directory internally), and requires truncation flag.
   */
   static const bool file_write( const std::string &file_contents, const std::string &file_name, const bool truncate_file );

   /*
      Writes a vector of strings to the specified file name (obtains working directory internally), and requires truncation flag.
   */
   static const bool file_write( const std::vector <std::string> &file_contents, const std::string &file_name, const bool truncate_file );

   /* 
      Read all the files listed in the save directory
   */
   static const bool save_files_find(const std::vector<std::string> &dir_content);

   /*
      Read all the content of a file in the save directory based on the user choosen file name
   */
   static const bool load_save_file(const std::vector<std::strinf> &file_contents, const std::string &filename);
};

#endif // _FILE_IO_HPP_
