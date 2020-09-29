
#ifndef _USER_INPUT_HPP_
#define _USER_INPUT_HPP_

#include "console.hpp"
#include "game_data.hpp"
#include "language.hpp"

class UserInput final {
public:
   /*
      Retrieves player input and returns the relevant CommandTag

      TODO (WraitheDX): This needs to be expanded to allow for typing in multi-command strings.
   */
   const CommandTag player_command_get( Language &language );

   /*
      Ask the player to enter the name of their character.
   */
   void player_name_get( Console &console, Language &language, GameData &game_data );

private:

};

#endif _USER_INPUT_HPP_
