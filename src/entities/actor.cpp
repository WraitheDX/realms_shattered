
#include "actor.hpp"

#include "../engine_systems/game_data.hpp"
#include "../engine_systems/logger.hpp"

Actor::Actor( GameData *game_data, const int UNIQUE_ID, const std::string name, const int health, const int damage ) :
   Entity( game_data, "entity_actor", UNIQUE_ID, name ),
   m_is_alive( true ),
   m_health_current( health ),
   m_health_max( health ),
   m_damage( damage )
{

}

void Actor::attack( ActionLog &action_log, const int target_id )
{
   Actor *actor( nullptr );
   if( !m_game_data->actor_get( target_id, actor ) ) {
      Logger( LoggerLevel::LOG_LEVEL_WARNING ).log() << "Actor::attack() made by " << name_get() << " unable to find target id: " << target_id; 
      return;
   }

   actor->health_current_set( actor->health_current_get() - damage_get() );
   action_log.add_line( name_get() + " attacks " + actor->name_get() + " for " + std::to_string( damage_get() ) + " damage." );
}

int Actor::damage_get()
{
   return m_damage;
}

int Actor::health_current_get()
{
   return m_health_current;
}

void Actor::health_current_set( const int health )
{
   m_health_current = health;
   health_check_bounds();
}

int Actor::health_max_get()
{
   return m_health_max;
}

void Actor::health_max_set( const int health )
{
   m_health_max = health;
   health_check_bounds();
}

void Actor::health_check_bounds()
{
   if( m_health_current < 0 ) {
      m_health_current = 0;
      m_is_alive = false;
   } else if( m_health_current > m_health_max ) {
      m_health_current = m_health_max;
   }
}

const bool Actor::is_alive_get()
{
   return m_is_alive;
}
