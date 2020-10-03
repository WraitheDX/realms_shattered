
#ifndef _USER_INPUT_HPP_
#define _USER_INPUT_HPP_

#include "console.hpp"
#include "game_data.hpp"
#include "language.hpp"

class UserInput final {
public:
   /*
   *  Retrieves player input and returns the relevant CommandTag.
   *
   *  TODO (WraitheDX): This needs to be expanded to allow for typing in multi-command strings.
   */
   const CommandTag player_command_get( Language &language );

   /*
   *  If player_input is an integer, fills player_number with integer stored, and returns true.
   */
   const bool player_input_is_number( int &player_number, std::string &player_input );

   /*
   *  Retrieves player input and fills commands_tags with all command tags found in string.
   * 
   *  Return value is the remainder of the string that did not hold valid commands tags.
   */
   std::string player_input_process( std::vector <CommandTag> &command_tags, Language &language );

   /*
   *  Asks the player to enter the language they prefer to play the game with, and returns the 2-character string of the language (Ex: en).
   */
   std::string player_language_get( Console &console, Language &language );

   /*
      Ask the player to enter the name of their character.
   */
   void player_name_get( Console &console, GameData &game_data, Language &language );

   /*
   *  Retrieves a raw string from the player's input.
   */
   std::string player_string_get();

   /*
   *  Asks the player to specify x/y offsets and width/height of the console area the game prints to.
   * 
   *  Game has a minimum width/height required to ensure proper alignment of things on the screen.
   */
   void print_dimensions_setup( Console &console, Language &language );

private:
   /*
   *  Breaks player input string into a vector of separate strings.
   */
   std::vector <std::string> player_input_break( std::string &player_input );
};

#endif _USER_INPUT_HPP_

