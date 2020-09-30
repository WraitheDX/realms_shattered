
#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <string>

#include "../engine_systems/console.hpp"
#include "../engine_systems/game_data.hpp"
#include "../engine_systems/language.hpp"
#include "../engine_systems/user_input.hpp"
#include "../engine_systems/user_interface.hpp"

enum class GameStateEnum {
   GAME_STATE_DEV_MENU,
   GAME_STATE_HELP,
   GAME_STATE_LOAD,
   GAME_STATE_PLAYER_HUB
};

class GameState final {
public:
   GameState( const std::string &game_title );

   const bool initialize();

   void run();

private:
   GameStateEnum m_game_state_current;

   std::string m_game_title;
   
   Console m_console;
   GameData m_game_data;
   Language m_language;
   UserInput m_user_input;
   UserInterface m_user_interface;

   void game_state_dev_menu();
   void game_state_help();
   void game_state_load();
   void game_state_player_hub();
};

#endif // _GAME_STATE_HPP_
