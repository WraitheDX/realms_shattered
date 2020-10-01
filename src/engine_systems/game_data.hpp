
#ifndef _GAME_DATA_HPP_
#define _GAME_DATA_HPP_

#include <vector>

class Actor;
class Entity;
struct Rift;

class GameData final {
public:
   GameData();
   ~GameData();

   /*
   *  Deletes all entity pointers (except for Player *) and clears the entity list.
   */
   void clear_entities();

   const bool is_game_running();
   
   /*
   *  Sets the m_game_running flag to false, allowing the engine to shut itself down.
   */
   void game_terminate();

   /*
   *  Creates a new, randomly generated rift.
   */
   void rift_create();

   /*
   *  Destroys current instance of rift.
   */
   void rift_destroy();

   Actor *player_get();
   Rift *rift_get();

private:
   bool m_game_running;

   std::vector <Entity *> m_entity_list;

   Actor *m_player;
   Rift *m_rift;
};

#endif // _GAME_DATA_HPP_
