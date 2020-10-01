
#include "game_data.hpp"

#include <random>

#include "../engine_systems/logger.hpp"
#include "../entities/actor.hpp"
#include "../entities/entity.hpp"
#include "../objects/rift.hpp"

GameData::GameData() :
   m_game_running( true ),
   m_entity_list(),
   m_player( nullptr ),
   m_rift( nullptr )
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
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Entities are being cleared";

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

const bool GameData::is_game_running()
{
   return m_game_running;
}

void GameData::game_terminate()
{
   m_game_running = false;
}

Actor *GameData::player_get()
{
   return m_player;
}

void GameData::rift_create()
{
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift is being created";
   rift_destroy();

   m_rift = new Rift();
   m_rift->m_difficulty = rand() % 3 + 1;
   m_rift->m_room_count = rand() % ( 3 + m_rift->m_difficulty ) + 1 + m_rift->m_difficulty;
   for( int room_iterator( 0 ); room_iterator < m_rift->m_room_count; ++room_iterator ) {
      m_rift->m_rooms.push_back( Room() );

      if( room_iterator + 1 == m_rift->m_room_count ) {
         m_rift->m_rooms[ room_iterator ].m_name = "Final Room";
      } else {
         m_rift->m_rooms[ room_iterator ].m_name = "Room " + std::to_string( room_iterator + 1 );
      }
   }

   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift difficulty: " << m_rift->m_difficulty;
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift room count: " << m_rift->m_rooms.size();
}

void GameData::rift_destroy()
{
   if( m_rift != nullptr ) {
      Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift is being destroyed";
      delete m_rift;
      m_rift = nullptr;
   }
}

Rift *GameData::rift_get()
{
   return m_rift;
}
