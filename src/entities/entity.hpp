
#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <string>

class Entity {
public:
   Entity( const int UNIQUE_ID, const std::string name );

   const int unique_id_get();
   const std::string &name_get();
   void name_set( const std::string name );

private:
   const int M_UNIQUE_ID;
   std::string m_name;
};

#endif // _ENTITY_HPP_
