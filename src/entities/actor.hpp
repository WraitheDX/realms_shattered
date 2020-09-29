
#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include <string>

#include "entity.hpp"

class Actor : public Entity {
public:
   Actor( const int UNIQUE_ID, const std::string name, const int health );

   const bool is_alive_get();

   int health_current_get();
   void health_current_set( const int health );
   int health_max_get();
   void health_max_set( const int health );

private:
   bool m_is_alive;

   int m_health_current;
   int m_health_max;

   /*
      Ensures that the player's current health does not go below zero or above health_max.
   */
   void check_health_bounds();
};

#endif // _ACTOR_HPP_
