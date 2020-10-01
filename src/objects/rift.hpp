
#ifndef _RIFT_HPP_
#define _RIFT_HPP_

#include <vector>

#include "room.hpp"

struct Rift {
   Rift() :
      m_difficulty( 0 ),
      m_room_count( 0 ),
      m_room_current( 0 ),
      m_rooms()
   {
   
   }

   int m_difficulty;
   int m_room_count;
   int m_room_current;

   std::vector <Room> m_rooms;
};

#endif // _RIFT_HPP_
