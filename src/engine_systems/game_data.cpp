
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
   m_player = new Actor( this, 1, "Player", 20, 3 );
   m_entity_list.push_back( m_player );
}

GameData::~GameData()
{
   clear_entities();

   delete m_player;
   m_entity_list.clear();
}

Actor *GameData::actor_create( const std::string name, const int health, const int damage )
{
   const int unique_id( unique_id_create() );
   Actor *actor( new Actor( this, unique_id, name, health, damage ) );

   m_entity_list.push_back( actor );

   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Actor created - Name: " << name << ", ID: " << actor->unique_id_get();
   return actor;
}

const bool GameData::actor_get( const int unique_id, Actor *&actor )
{
   const int entity_list_size( m_entity_list.size() );
   for( int iterator( 0 ); iterator < entity_list_size; ++iterator ) {
      if( m_entity_list[ iterator ]->unique_id_get() == unique_id ) {
         if( m_entity_list[ iterator ]->inherited_class_get() == "entity_actor" ) {
            actor = static_cast<Actor *>( m_entity_list[ iterator ] );
            return true;
         }
      }
   }

   actor = nullptr;
   return false;
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

      entity_destroy( (*entity_iter)->unique_id_get() );
   }
}

void GameData::entity_destroy( const int unique_id )
{
   const int entity_list_size( m_entity_list.size() );
   for( int iterator( 0 ); iterator < entity_list_size; ++iterator ) {
      if( m_entity_list[ iterator ]->unique_id_get() == unique_id ) {
         // After finding the unique_id, cast to the correct entity type to ensure proper deletion.
         Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Deleting entity - Name: " << m_entity_list[ iterator ]->name_get()
                                                     << ", ID: " << unique_id;
         if( m_entity_list[ iterator ]->inherited_class_get() == "entity_entity" ) {
            delete m_entity_list[ iterator ];
         } else if( m_entity_list[ iterator ]->inherited_class_get() == "entity_actor" ) {
            Actor *actor = static_cast<Actor *>( m_entity_list[ iterator ] );
            delete actor;
         }

         m_entity_list.erase( m_entity_list.begin() + iterator );
         break;
      }
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
   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift difficulty: " << m_rift->m_difficulty;

   for( int room_iterator( 0 ); room_iterator < m_rift->m_room_count; ++room_iterator ) {
      m_rift->m_rooms.push_back( Room() );

      if( room_iterator + 1 == m_rift->m_room_count ) {
         m_rift->m_rooms[ room_iterator ].m_name = "Final Room";
      } else {
         m_rift->m_rooms[ room_iterator ].m_name = "Room " + std::to_string( room_iterator + 1 );
      }

      int spawn_enemy_roll( rand() % 100 + 1 );
      if( spawn_enemy_roll < ( m_rift->m_difficulty * 20 ) ) {
         Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << m_rift->m_rooms.back().m_name << " spawned an enemy";
         Actor *enemy( actor_create( "Enemy", 5, 2 ) );
         m_rift->m_rooms.back().m_entity_list.push_back( enemy );
      }
   }

   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift room count: " << m_rift->m_rooms.size();
}

void GameData::rift_destroy()
{
   if( m_rift == nullptr ) {
      return;
   }

   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Rift is being destroyed";

   for( int room_iterator( 0 ); room_iterator <  m_rift->m_rooms.size(); ++room_iterator ) {
      if( !m_rift->m_rooms[ room_iterator ].m_entity_list.empty() ) {
         for( int entity_iterator( 0 ); entity_iterator < m_rift->m_rooms[ room_iterator ].m_entity_list.size(); ++entity_iterator ) {
            entity_destroy( m_rift->m_rooms[ room_iterator ].m_entity_list[ entity_iterator ]->unique_id_get() );
         }
      }
   }

   delete m_rift;
   m_rift = nullptr;
}

Rift *GameData::rift_get()
{
   return m_rift;
}

const int GameData::unique_id_create()
{
   bool is_id_unique( true );
   int unique_id( 2 );
   const int ENTITY_LIST_SIZE( m_entity_list.size() );

   // Increment the unique_id value if it is already used by another entity, then redo the check against the entire entity list.
   do {
      is_id_unique = true;
      for( int iterator( 0 ); iterator < ENTITY_LIST_SIZE; ++iterator ) {
         if( unique_id == m_entity_list[ iterator ]->unique_id_get() ) {
            is_id_unique = false;
            ++unique_id;
            break;
         }
      }
   } while( is_id_unique == false );

   Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "UniqueID value: " << unique_id;
   return unique_id;
}
