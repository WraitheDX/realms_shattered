
#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <string>

#include "../engine_systems/action_log.hpp"
#include "../engine_systems/console.hpp"
#include "../engine_systems/game_data.hpp"
#include "../engine_systems/language.hpp"
#include "../engine_systems/user_input.hpp"
#include "../engine_systems/user_interface.hpp"

enum class GameStateEnum {
   GAME_STATE_DEV_MENU,
   GAME_STATE_HELP,
   GAME_STATE_LOAD,
   GAME_STATE_MAIN_MENU,
   GAME_STATE_PLAYER_HUB,
   GAME_STATE_RIFT
};

class GameState final {
public:
   GameState( const std::string &game_title );

   /*
   *  Initialize all of the game systems that are needed to run the game.
   */
   const bool initialize();

   /*
   *  Continues to process the current game state until the game ends.
   */
   void run();

private:
   GameStateEnum m_game_state_current;

   std::string m_game_title;
   
   ActionLog m_action_log;
   Console m_console;
   GameData m_game_data;
   Language m_language;
   UserInput m_user_input;
   UserInterface m_user_interface;

   /*
   *  The developer menu allows the player to use developer commands to do various things. Essentially a cheat menu used to assist in development.
   */
   void game_state_dev_menu();

   /*
   *  A help menu that should display available commands and give general info on how to play the game.
   */
   void game_state_help();

   /*
   *  Used to show the player a listing of all of the save files found, and allow the player to load one of them and continue their game.
   */
   void game_state_load();

   /*
   *  Menu the game should load into after initialization. Basic options should include: New game, load game, help, settings, quit.
   */
   void game_state_main_menu();

   /*
   *  The menu where that acts as the player's 'home'. Player is here between adventures, talking with npcs, etc.
   */
   void game_state_player_hub();

   /*
   *  Here the player will explore generated rifts composed of rooms.
   */
   void game_state_rift();

   /*
   *  Asks the player to specify x/y offsets and width/height of the console area the game prints to.
   * 
   *  Game has a minimum width/height required to ensure proper alignment of things on the screen.
   */
   void print_dimensions_setup();
   /*
      To save all persistent game data of the player's in a file with the character name in the save folder.
   */
   void game_state_save();
};

#endif // _GAME_STATE_HPP_
