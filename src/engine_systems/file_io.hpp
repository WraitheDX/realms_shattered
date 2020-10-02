
#ifndef _FILE_IO_HPP_
#define _FILE_IO_HPP_

#include <map>
#include <string>
#include <vector>

#include "action_log.hpp"
#include "config_file.hpp"
#include "game_data.hpp"

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
   *  Reads a file as a vector of strings, filling the 'file_contents' parameter with the contents of the file.
   */
   static const bool file_read( std::vector <std::string> &file_contents, const std::string &file_name );

   /*
   *  Writes a single string to the specified file name (obtains working directory internally), and requires truncation flag.
   */
   static const bool file_write( const std::string &file_contents, const std::string &file_name, const bool truncate_file );

   /*
   *  Reads the file specified and fills parsed_tags with key/value pairs from the file.
   * 
   *  Returns success flag.
   */
   static const bool file_tags_parse( std::map <std::string, std::string> &parsed_tags, const std::string &file_name );

   /*
   *  Writes a vector of strings to the specified file name (obtains working directory internally), and requires truncation flag.
   */
   static const bool file_write( const std::vector <std::string> &file_contents, const std::string &file_name, const bool truncate_file );

   /*
   *  Creates specified folder.
   * 
   *  Appends folder name to current working directory.
   */
   static void folder_create( const std::string &folder_name );

   /*
   *  Returns true if folder_name exists.
   * 
   *  Appends folder name to current working directory.
   */
   static const bool folder_exists( const std::string &folder_name );

   /* 
   *  Read all the files listed in the save directory
   */
   static const bool player_files_find( std::vector<std::string> &dir_content );

   /*
   *  Read all the content of a file in the save directory based on the user choosen file name
   */
   static const bool player_file_load( GameData &game_data, const std::string &file_name );

   /*
   *  Write the player's data in the Save folder 
   */
   static const bool player_file_save( ActionLog &action_log, GameData &game_data );

};

#endif // _FILE_IO_HPP_
