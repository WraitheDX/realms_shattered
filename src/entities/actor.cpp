
#include "actor.hpp"

Actor::Actor( const int UNIQUE_ID, const std::string name, const int health ) :
   Entity( UNIQUE_ID, name ),
   m_is_alive( true ),
   m_health_current( health ),
   m_health_max( health )
{

}

int Actor::health_current_get()
{
   return m_health_current;
}

void Actor::health_current_set( const int health )
{
   m_health_current = health;
   check_health_bounds();
}

int Actor::health_max_get()
{
   return m_health_max;
}

void Actor::health_max_set( const int health )
{
   m_health_max = health;
   check_health_bounds();
}

void Actor::check_health_bounds()
{
   if( m_health_current < 0 ) {
      m_health_current = 0;
      m_is_alive = false;
   } else if( m_health_current > m_health_max ) {
      m_health_current = m_health_max;
   }
}
