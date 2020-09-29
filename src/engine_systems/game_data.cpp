
#include "game_data.hpp"

#include "../entities/actor.hpp"
#include "../entities/entity.hpp"

GameData::GameData() :
   m_entity_list(),
   m_player( nullptr )
{
   // Player should be available from beginning to end, and always have the unique_id of 1
   m_player = new Actor( 1, "Player", 1 );
   m_entity_list.push_back( m_player );
}

GameData::~GameData()
{
   clear_entities();

   delete m_player;
   m_entity_list.clear();
}

void GameData::clear_entities()
{
   std::vector <Entity *>::iterator entity_iter( m_entity_list.begin() );
   for( ; entity_iter != m_entity_list.end(); ++entity_iter ) {
      // Skip the player entity, which should exist until the end of the game.
      if( (*entity_iter)->unique_id_get() == m_player->unique_id_get() ) {
         continue;
      }

      if( (*entity_iter) != nullptr ) {
         delete (*entity_iter);
      }

      m_entity_list.erase( entity_iter );
   }
}

Actor *GameData::player_get()
{
   return m_player;
}
