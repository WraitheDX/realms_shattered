
#ifndef _GAME_DATA_HPP_
#define _GAME_DATA_HPP_

#include <vector>

class Entity;
class Actor;

class GameData final {
public:
   GameData();
   ~GameData();

   void clear_entities();

private:
   std::vector <Entity *> m_entity_list;

   Actor *m_player;
};

#endif // _GAME_DATA_HPP_
