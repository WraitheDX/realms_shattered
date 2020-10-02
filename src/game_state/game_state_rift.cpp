
#include "game_state.hpp"

#include "../engine_systems/logger.hpp"
#include "../entities/actor.hpp"
#include "../objects/rift.hpp"

void GameState::game_state_rift()
{
   static const std::string NAME_RIFT_STATE = "The Rifts";
   std::string name_room( "Room INVALID" );

   Rift * rift( m_game_data.rift_get() );
   if( rift != nullptr ) {
      name_room = rift->m_rooms[ rift->m_room_current ].m_name;
   }

   m_console.print_box( 0, 0, m_console.width_get(), m_console.height_get(), '+' );
   m_console.print( NAME_RIFT_STATE, ( ( m_console.width_get() / 2 ) - ( NAME_RIFT_STATE.length() / 2 ) ), 1 );
   m_console.print( name_room, ( ( m_console.width_get() / 2 ) - ( name_room.length() / 2 ) ), 2 );
   
   if( rift != nullptr &&
       !rift->m_rooms[ rift->m_room_current ].m_entity_list.empty() ) {
      m_action_log.add_line( "You see " + rift->m_rooms[ rift->m_room_current ].m_entity_list[ 0 ]->name_get() + " before you." );
   }

   m_user_interface.player_stats_brief_display( m_console, m_language, m_game_data );
   m_user_interface.action_log_display( m_action_log, m_console );
   m_user_interface.command_prompt_display( m_console, m_language );
   CommandTag command_tag( m_user_input.player_command_get( m_language ) );
   
   bool player_turn_taken( false );
   switch( command_tag ) {
      case CommandTag::COMMAND_INVALID:
         break;
      case CommandTag::COMMAND_ATTACK:
         if( rift != nullptr &&
             !rift->m_rooms[ rift->m_room_current ].m_entity_list.empty() ) {
            Actor *enemy( nullptr );
            if( m_game_data.actor_get( rift->m_rooms[ rift->m_room_current ].m_entity_list[ 0 ]->unique_id_get(), enemy ) ) {
               m_game_data.player_get()->attack( m_action_log, enemy->unique_id_get() );

               if( !enemy->is_alive_get() ) {
                  m_action_log.add_line( m_game_data.player_get()->name_get() + " has defeated " + enemy->name_get() );
                  m_game_data.entity_destroy( enemy->unique_id_get() );
                  rift->m_rooms[ rift->m_room_current ].m_entity_list.erase( rift->m_rooms[ rift->m_room_current ].m_entity_list.begin() );
               }
               
               player_turn_taken = true;
            }
         } else {
            m_action_log.add_line( "There is nothing there to attack..." );
         }

         break;
      case CommandTag::COMMAND_MOVE:
         if( rift != nullptr ) {
            if( !rift->m_rooms[ rift->m_room_current ].m_entity_list.empty() ) {
               m_action_log.add_line( "You cannot move on until the enemy has been defeated!" );
               break;
            }

            ++rift->m_room_current;

            if( rift->m_room_current >= rift->m_room_count ) {
               Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player has cleared the rift";
               m_action_log.add_line( m_game_data.player_get()->name_get() + " has cleared the rift!" );
               m_game_data.rift_destroy();
               m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
            } else {
               Logger( LoggerLevel::LOG_LEVEL_INFO ).log() << "Player moved to room: " << rift->m_room_current + 1;
               m_action_log.add_line( m_game_data.player_get()->name_get() + " has entered " + name_room );
            }
         }
         break;
      case CommandTag::COMMAND_QUIT:
         m_game_data.game_terminate();
         break;
   }

   // If any entity occupies the current room and player has acted, allow entities their turn.
   rift = m_game_data.rift_get();
   if( rift != nullptr &&
       !rift->m_rooms[ rift->m_room_current ].m_entity_list.empty() &&
       player_turn_taken ) {
      Actor *actor( nullptr );
      if( m_game_data.actor_get( rift->m_rooms[ m_action_log, rift->m_room_current ].m_entity_list[ 0 ]->unique_id_get(), actor ) ) {
         actor->attack( m_action_log, m_game_data.player_get()->unique_id_get() );

         if( !m_game_data.player_get()->is_alive_get() ) {
            m_action_log.add_line( m_game_data.player_get()->name_get() + " has been struck down be " + actor->name_get() );
            m_game_data.rift_destroy();
            m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
         }
      }
   }
      
   m_console.clear();
}
