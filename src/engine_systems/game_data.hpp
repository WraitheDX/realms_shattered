
#ifndef _GAME_DATA_HPP_
#define _GAME_DATA_HPP_

#include <string>
#include <vector>

class Actor;
class Entity;
struct Rift;

class GameData final {
public:
   GameData();
   ~GameData();

   /*
   *  Create a new Actor with a unique_id and add them to the entity list.
   */
   Actor *actor_create( const std::string name, const int health, const int damage );

   /*
   *  Create a new Actor from the file specified with a unique_id and add them to the entity list.
   */
   Actor *actor_create_from_file( const std::string &file_path );

   /*
   *  Finds actor by their unique_id value and populates *actor if found.
   * 
   *  Returns false if unique_id was not found, or if the unique_id found is not of type Actor.
   */
   const bool actor_get( const int unique_id, Actor *&actor );

   /*
   *  Deletes all entity pointers (except for Player *) and clears the entity list.
   */
   void clear_entities();

   /*
   *  Finds entity by their unique_id value, safely deletes them, and erases their slot in entity_list.
   */
   void entity_destroy( const int unique_id );

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

   /*
   *  Searches through entity_list and returns an unused unique_id number
   */
   const int unique_id_create();
};

#endif // _GAME_DATA_HPP_
