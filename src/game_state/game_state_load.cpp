
#include "game_state.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <string.h>
#include <file_io.hpp>
using namespace std;
void GameState::game_state_load()
{  char done = 'n';
   vector <string> saved_files;
   bool found_save_folder;
   // read all the files in the save directory
   found_save_folder = FileIO::save_files_find(saved_files);
   if (!found_save_folder)
      {
         cout<<" No save files found\n";
         return;
      }
  repeat:
   cout<<"Your saved files are \t\t";
   for (auto i = saved_files.begin() ; i != saved_files.end(); i++){
      cout << i+1 << " - " << *i;
   }
   cout << "Please type the exact name of the game you want to load \n";
   string choosen_file;
   getline(cin, choosen_file);
   // to read the file 

   vector<string> file_content;
   bool correct_name = FileIO::save_files_find(&file_content, &choosen_file);
   if (!correct_name)
     { cout<<"Sorry, Could not find this file. \t\t press Y/y if you want to try again\n"
      cin >> done;
      if (done == 'y' || done == 'Y')
         goto repeat;
     }

  // m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
}
