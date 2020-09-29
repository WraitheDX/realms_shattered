
#ifndef _LANGUAGE_HPP_
#define _LANGUAGE_HPP_

#include <map>
#include <string>

enum class CommandTag {
   COMMAND_INVALID = 0,
   COMMAND_QUIT
};

class Language final {
public:
   /*
      Load list of commands in specified (language) file.

      Ex: commands_load( "data/language/en_commands.txt" )
   */
   const bool commands_load( const std::string &file_name );

   /*
      Returns true if 'command_tag' is found in commands_map, and fills command_value with value paired with the found key.
   */
   const CommandTag command_tag_get( const std::string &player_input );

private:
   std::map <std::string, std::string> commands_map;
};

#endif // _LANGUAGE_HPP_
