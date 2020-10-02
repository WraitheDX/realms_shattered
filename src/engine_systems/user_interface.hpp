
#ifndef _USER_INTERFACE_HPP_
#define _USER_INTERFACE_HPP_

#include "action_log.hpp"
#include "console.hpp"
#include "game_data.hpp"
#include "language.hpp"

class UserInterface final {
public:
   /*
   *  Print the <display_size_current> most recent actions in the log.
   */
   void action_log_display( ActionLog &action_log, Console &console );

   /*
   *  Displays the command prompt where the player types in their input.
   *
   *  NOTE: Does not receive input.
   */
   void command_prompt_display( Console &console, Language &language );

   /*
   *  Pauses the game and displays the pause message at the bottom of the screen.
   */
   void pause_and_display_message( Console &console );

   /*
   *  Displays a brief view of the player's stats, generally the stats the player should see constantly (name, health, etc).
   */
   void player_stats_brief_display( Console &console, Language &language, GameData &game_data );

private:
   
};

#endif // _USER_INTERFACE_HPP_
