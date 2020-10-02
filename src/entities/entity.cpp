
#include "entity.hpp"

#include "../engine_systems/game_data.hpp"

Entity::Entity( GameData *game_data, const std::string inherited_class, const int unique_id, const std::string name ) :
   m_game_data( game_data ),
   m_inherited_class( inherited_class ),
   m_unique_id( unique_id ),
   m_name( name )
{
   
}

const std::string &Entity::inherited_class_get()
{
   return m_inherited_class;
}

const int Entity::unique_id_get()
{
   return m_unique_id;
}

const std::string &Entity::name_get()
{
   return m_name;
}

void Entity::name_set( const std::string name )
{
   m_name = name;
}
