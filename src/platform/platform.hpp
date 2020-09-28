
#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#ifdef _WIN32
   #include <direct.h>
#endif // _WIN32

/*
   Used to obtain the execution path of the game from specific platform libraries (Windows, Linux, Mac).

   Currently does not check to ensure a path is actually obtained, and only have the code for Windows.
*/
const std::string get_working_directory()
{
   // If working directory has already been obtained, use it.
   static std::string working_directory( "INVALID" );
   if( working_directory != "INVALID" ) {
      return working_directory;
   }

   // TODO (WraitheDX): Abstract below and the reference to direct.h above into a platform layer
   #ifdef _WIN32
   {
      char buffer[FILENAME_MAX];
      _getcwd( buffer, FILENAME_MAX );

      working_directory = buffer;
   }
   #endif // _WIN32

   return working_directory;
}

#endif // _PLATFORM_HPP_
