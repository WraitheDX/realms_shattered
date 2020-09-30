
#ifndef _USER_INPUT_HPP_
#define _USER_INPUT_HPP_

#include "console.hpp"
#include "game_data.hpp"
#include "language.hpp"

class UserInput final {
public:
   /*
   *  Retrieves player input and returns the relevant CommandTag
   *
   *  TODO (WraitheDX): This needs to be expanded to allow for typing in multi-command strings.
   */
   const CommandTag player_command_get( Language &language );

   /*
   *  Retrieves a raw string from the player's input
   */
   std::string player_string_get();

private:

};

#endif _USER_INPUT_HPP_
