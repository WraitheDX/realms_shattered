
#include "game_state.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <string.h>
using namespace std;
void GameState::game_state_load()
{  char done = 'n';
   vector <string> saved_files;
   // read all the files in the save directory
   DIR * dir = opendir ("/save");
   struct dirent *entry;
   if (dir == NULL)
      cout<<" No save files found\n";
   else   
   {
      string filename;
      while((entry = readdir(dir)) != NULL){
         filename = entry->d_name;
         saved_files.push_back(filename.substr(0,filename.size()-4));
      }
   }
   closedir(dir);
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
   string path = "/save/" + choosen_file;
   ifstream file(path);
   if (!file.open()){
      cout<<"Sorry, Could not find this file. \t\t press Y/y if you want to try again\n"
      cin >> done;
      if (done == 'y' || done == 'Y')
         goto repeat;
   }
   else {
      while(!file.eof()){
         string file_line("");
         getline(file, file_line);
         file_content.push_back(file_line);
      }
      // now the file_content contains the file data 
   }
   

  // m_game_state_current = GameStateEnum::GAME_STATE_PLAYER_HUB;
}
