
#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <string>

class GameData;

class Entity {
public:
   Entity( GameData *game_data, const std::string inherited_class, const int unique_id, const std::string name );

   const std::string &inherited_class_get();
   const int unique_id_get();

   const std::string &name_get();
   void name_set( const std::string name );

protected:
   /*
   *  Pointer reference to game data that owns all entities.
   * 
   *  Used to allow entities to interact with one another.
   */
   GameData *m_game_data;

private:
   // This variable tells us what class to cast this entity to when we need to use it during runtime.
   std::string m_inherited_class;

   const int m_unique_id;
   std::string m_name;
};

#endif // _ENTITY_HPP_
