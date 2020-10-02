
#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include <string>

#include "entity.hpp"
#include "../engine_systems/action_log.hpp"

class GameData;

class Actor : public Entity {
public:
   Actor( GameData *game_data, const int unique_id, const std::string name, const int health, const int damage );

   void attack( ActionLog &action_log, const int target_id );

   const bool is_alive_get();

   int damage_get();

   /*
   *  Functions for getting and setting the current and max health of the Actor.
   */
   int health_current_get();
   void health_current_set( const int health );
   int health_max_get();
   void health_max_set( const int health );

private:
   bool m_is_alive;

   int m_health_current;
   int m_health_max;

   int m_damage;

   /*
      Ensures that the player's current health does not go below zero or above health_max.
   */
   void health_check_bounds();
};

#endif // _ACTOR_HPP_
