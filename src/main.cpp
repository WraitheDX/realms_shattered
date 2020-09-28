
#include <iostream>
#include <string>

#ifdef _WIN32
   #include <direct.h>
#endif // _WIN32

#include "engine_systems/logger.hpp"

const
std::string get_working_directory()
{
   std::string working_directory("");

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

int main( char ** argument_strings, int argument_count )
{
   Logger::set_logger_level( LoggerLevel::LOG_LEVEL_INFO );
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initializing";
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";

   std::cout<< "Hello\n";

   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is shutting down";
   system("pause");

   return 0;
}
