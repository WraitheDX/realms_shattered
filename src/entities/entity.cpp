
#include "entity.hpp"

Entity::Entity( const int UNIQUE_ID, const std::string name ) :
   M_UNIQUE_ID( UNIQUE_ID ),
   m_name( name )
{
   
}

const int Entity::unique_id_get()
{
   return M_UNIQUE_ID;
}

const std::string &Entity::name_get()
{
   return m_name;
}

void Entity::name_set( const std::string name )
{
   m_name = name;
}
