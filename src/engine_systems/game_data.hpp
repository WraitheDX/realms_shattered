
#ifndef _GAME_DATA_HPP_
#define _GAME_DATA_HPP_

#include <vector>

class Entity;
class Actor;

class GameData final {
public:
   GameData();
   ~GameData();

   /*
      Deletes all entity pointers (except for Player *) and clears the entity list.
   */
   void clear_entities();

   Actor *player_get();

private:
   std::vector <Entity *> m_entity_list;

   Actor *m_player;
};

#endif // _GAME_DATA_HPP_
