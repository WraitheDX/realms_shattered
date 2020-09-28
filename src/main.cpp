
#include <iostream>
#include <string>

#include "engine_systems/logger.hpp"

int main( char ** argument_strings, int argument_count )
{
   Logger::set_logger_level( LoggerLevel::LOG_LEVEL_INFO );
   Logger::create_new_log_file();
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initializing";
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initialized";

   std::cout << "Hello\n";

   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is shutting down";
   system("pause");

   return 0;
}
