
#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <random>
#include <string>
#include <vector>

#include "../entities/entity.hpp"

struct Room {
   Room() :
      m_name( "Room" ),
      m_entity_list()
   {
      
   }

   std::string m_name;

   std::vector <Entity *> m_entity_list;
};

#endif // _ROOM_HPP_
