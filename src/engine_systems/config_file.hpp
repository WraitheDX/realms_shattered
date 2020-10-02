
#ifndef _CONFIG_FILE_HPP_
#define _CONFIG_FILE_HPP_

struct ConfigFile {
   ConfigFile():
      m_language( "INVALID" ),
      m_game_width( 0 ),
      m_game_height( 0 ),
      m_game_offset_x( 0 ),
      m_game_offset_y( 0 )
   {
   
   }
   std::string m_language;

   int m_game_width;
   int m_game_height;
   int m_game_offset_x;
   int m_game_offset_y;
};

#endif // _CONFIG_FILE_HPP_
