
#ifndef _RIFT_HPP_
#define _RIFT_HPP_

#include <vector>

#include "room.hpp"

struct Rift {
   Rift();

   int m_difficulty;
   int m_room_count;
   int m_room_current;

   std::vector <Room> m_rooms;
};

#endif // _RIFT_HPP_
