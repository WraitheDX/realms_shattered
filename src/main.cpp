
#include <string>

#include "game_state/game_state.hpp"
#include "engine_systems/logger.hpp"

int main( char ** argument_strings, int argument_count )
{
   // Start the initialization of the game by setting up the Logger class to log game data and errors for us.
   Logger::set_logger_level( LoggerLevel::LOG_LEVEL_INFO );
   Logger::create_new_log_file();
   
   const std::string GAME_TITLE = "Realms Shattered v0.0";
   GameState game_state( GAME_TITLE );

   // The game is now ready to initialize the systems that allow the engine to run the game.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is initializing";
   if( !game_state.initialize() ) {
      Logger( LoggerLevel::LOG_LEVEL_ERROR ).log() << "Realms failed to initialize.";
   }

   game_state.run();

   // The game has now left the gameplay loop and will shut down any systems that require being shut down.
   Logger( LoggerLevel::LOG_LEVEL_PROGRESS ).log() << "Realms Shattered is shutting down";

   return 0;
}
