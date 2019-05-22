#include "LinkedList.h"
#include "CheckFormat.h"
#include "qwirkle.h"

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream

// transform all borad's tiles to string 
// if console is true , display tiles has colour , if not doesn't have colour(save to file)
std::string DisplayBoard(bool console) {
   std::ostringstream stream;
   stream << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" << std::endl;
   stream << "------------------------------------------------------------------------------------" << std::endl;
   for (size_t i = 0; i < ROW; ++i) {
      stream << (char)('A' + i ) << " " << "|";
      for (size_t j = 0; j < COLUMN; ++j) {
         if (board[i][j]->shape == -1) {
            stream << "  " << "|";
         } else {
            if (console) {
               stream << colourMap.at((board[i][j]->colour)) << board[i][j]->colour << board[i][j]->shape << colourMap.at('W');
            } else {
               stream << board[i][j]->colour << board[i][j]->shape;
            }
            
            stream  << "|";
         }
      }
      stream << std::endl;
   }

   return stream.str();
}

std::string DisplayBoardUnicode() {
   std::ostringstream stream;
   stream << "   0   2   4   6   8   10  12  14  16  18  20  22  24  " << std::endl;
   stream << "     1   3   5   7   9   11  13  15  17  19  21  23  25" << std::endl;
   stream << "---------------------------------------------------------" << std::endl;
   for (size_t i = 0; i < ROW; ++i) {
      stream << (char)('A' + i ) << " " << "|";
      for (size_t j = 0; j < COLUMN; ++j) {
         if (board[i][j]->shape == -1) {
            stream << " " << "|";
         } else {
            stream << colourMap.at((board[i][j]->colour)) << unicodeMap[board[i][j]->shape] << colourMap.at('W');
            stream  << "|";
         }
      }
      stream << std::endl;
   }

   for (size_t i = 0; i < COLOUR_SIZE; ++i) {
      stream << colour[i] << ":" << colourMap.at(colour[i]) << colour[i] << colourMap.at('W') << "  ";
   }
   stream << std::endl;
   for (size_t i = 0; i < SHAPE_SIZE; ++i) {
      stream << shape[i] << ":" << unicodeMap.at(shape[i]) << "  ";
   }
   stream << std::endl;

   return stream.str();
}

// display player's hand and current board's tiles
void DisplayGame(int id) {
   std::cout << playerNames[id] << ", it’s your turn" << std::endl;
   for (size_t i = 0; i < playerNum; ++i) {
      std::cout << "Score for " << playerNames[i] << ": " << playerScores[i] << std::endl;
   }

   if (unicode) {
      std::cout << DisplayBoardUnicode();
      std::cout << "Your hand is" << std::endl << playerHands[id]->GetTiles(true, unicode) << std::endl;
   } else {
      std::cout << DisplayBoard(true);
      std::cout << "Your hand is" << std::endl << playerHands[id]->GetTiles(true, unicode) << std::endl;
   }
   
}

// print menu 
void PrintMenuMessage() {
   std::cout << "Menu" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Show student information" << std::endl;
   std::cout << "4. Quit" << std::endl;
}

// my students info
void PrintStudentInformation() {
   std::cout << "-------------------" << std::endl;
   // first 
   std::cout << "Name: <full name>" << std::endl;
   std::cout << "Student ID: <student number>" << std::endl;
   std::cout << "Email: <email address>" << std::endl;
   // second ...
   std::cout << std::endl << "Name: <full name>" << std::endl;

   std::cout << "-------------------" << std::endl;
}

// winner info
void PrintGameOverInformation() {
   std::cout << "Game over" << std::endl;
   size_t maxScore = 0;
   int winner = 0;
   for (size_t i = 0; i < playerNum; ++i) {
      std::cout << "Score for <" << playerNames[i] << ">: " << playerScores[i] << std::endl;
      if (playerScores[i] > maxScore) {
         winner = i;
         maxScore = playerScores[i];
      }
   }

   std::cout << "Player <" << playerNames[winner] << "> won!" << std::endl;
}

// print the priority queue of the highscores
void PrintHighScores() {
   std::priority_queue<Score> highScoresTmp;
   std::vector<Score> scores;
   while (!highScores.empty()) {
      Score s = highScores.top();
      scores.push_back(s);
      highScores.pop();
      highScoresTmp.push(s);
   }
   highScores.swap(highScores);

   int num = scores.size();
   if (num == 0) {
      std::cout << "No highscores." << std::endl;
   } else {
      std::cout << std::endl << "#  " << "Name  " << "Score " << std::endl;
      for (int i = 0; i < num; ++i) {
         std::cout << i + 1 << ". " << scores[i].name << "   " << scores[i].score << std::endl;
      }
   }
}

// for help command  see 4.1.1 Help! 
void PrintHelpMessage() {
   std::cout << "-------  help  ------------" << std::endl;
   std::cout << "You can input the following actions: " << std::endl;
   std::cout << "place <tile> at <grid location>" << std::endl;
   std::cout << "replace <tile>" << std::endl;
   std::cout << "restart(restart a new game)" << std::endl;
   std::cout << "highscore(display the list of high scores achieved by any player who has played your game of Qwirkle)" << std::endl;
   std::cout << "quit(quit the game)" << std::endl;

   std::cout << "-------------------" << std::endl;
}

// get user's input path
void InputGamePath(std::string &path) {
   std::cout << "Enter the filename from which load a game" << std::endl;
   std::cin >> path;
}

bool LoadGame(std::string path, int &start) {
   std::string name, handTiles;
   size_t score;
   std::ifstream ifs(path);
   if (ifs.is_open()) {
      // load player's name,score and hand
      playerNum = 0;
      char line[256];
      while (ifs.getline(line, 256)) {
         std::string str(line);
         // std::cout << "Cur line: " << str << std::endl;
         if (str.find(" ") == std::string::npos) {
            ifs >> score >> handTiles;
            ifs.ignore();
            playerNames.push_back(line);
            playerScores.push_back(score);

            // load player's hand tiles 
            LinkedList* list = new LinkedList();
            std::stringstream ss(handTiles);
            std::string tile;
            std::vector<std::string> tiles;
            Tile* tp;
            //  "," split tiles
            while (std::getline(ss, tile, ',')) {
               tiles.push_back(tile);
            }
            for (size_t k = 0; k < tiles.size(); ++k) {
               if ((tp = CheckTile(tiles[k])) != nullptr) {
                  list->InsertTileToTail(tp);
               }
            }
            playerHands.push_back(list);

            playerNum++;
            // std::cout << "Num: " << playerNum << name << " " << score << std::endl;
         } else {
            // break while loop if get "0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25"
            break;
         }
      }

      // discard line "------------------------------------------------------------------------------------"
      ifs.getline(line, 256);
      
      // load board  
      for (size_t k = 0; k < ROW; ++k) {
         ifs.getline(line, 256);
         // std::cout << line << std::endl;
         std::string lineBoard(line);
         if (lineBoard.size() >= 81) {
            // TODO check line size
         }

         std::stringstream ss(lineBoard);
         std::string tile;
         std::vector<std::string> tiles;
         Tile* tp;
         std::getline(ss, tile, '|');
         while (std::getline(ss, tile, '|')) {
            tiles.push_back(tile);
         }
         for (size_t i = 0; i < tiles.size(); ++i) {
            if ((tp = CheckTile(tiles[i])) != nullptr) {
               board[k][i] = tp;
            } else {
               Tile* t = new Tile(' ', -1);
               board[k][i] = t;
            }
         }
      }
      
      // for debug 
      // std::cout << DisplayBoard(true);

      // load bag's tiles 
      std::string handTiles, player;
      ifs >> handTiles;
      listBag = new LinkedList();
      std::stringstream ss(handTiles);
      std::string tile;
      std::vector<std::string> tiles;
      Tile* tp;
      while (std::getline(ss, tile, ',')) {
         tiles.push_back(tile);
      }
      for (size_t k = 0; k < tiles.size(); ++k) {
         if ((tp = CheckTile(tiles[k])) != nullptr) {
            listBag->InsertTileToTail(tp);
         }
      }

      // for debug  
      // std::cout << listBag->GetTiles() << std::endl;

      // load cur player, it's start-th player
      ifs >> player;
      for (size_t i = 0; i < playerNames.size(); ++i) {
         if (player.compare(playerNames[i]) == 0) {
            start = i;
         }
      }

      // for debug 
      // std::cout << player  << " " << start << std::endl;

      // load high scores
      int score;
      std::string name;
      while (ifs >> name >> score) {
         highScores.push(Score(name, score));
      }

   } else {
      return false;
   }

   return true;
}

// save game to path, id is the current player
bool SaveGame(std::string path, int id) {
   std::ofstream ofs;
   ofs.open(path, std::ofstream::out | std::ofstream::trunc);

   if (ofs.is_open()) {
      // save player name,scores,handtiles
      for (size_t i = 0; i < playerNum; ++i) {
         ofs << playerNames[i] << std::endl;
         ofs << playerScores[i] << std::endl;
         std::string handTile = playerHands[i]->GetTiles(false, unicode);
         ofs << handTile << std::endl;
      }
      // save board
      ofs << DisplayBoard(false);
      // save bagtiles
      ofs << listBag->GetTiles(false, unicode) << std::endl;
      // save current player's name 
      ofs << playerNames[id] << std::endl;
      // save the highscores 
      std::priority_queue<Score> highScoresTmp;
      while (!highScores.empty()) {
         Score ts = highScores.top();
         ofs << ts.name << std::endl << ts.score << std::endl;
         highScoresTmp.push(ts);
         highScores.pop();
      }
      highScores.swap(highScoresTmp);
   } else {
      std::cout << "open file failed" << std::endl;
      return false;
   }

   return true;
}

bool InputPlayerName(std::string &playerName, int id) {
   // bool once = false;
   do {
      std::cout << std::endl << "Enter a name for player" << id << "(uppercase characters only)" << std::endl;
      std::cout << "> ";
      // input name error, return false
      if (std::cin >> playerName) {
         if (!CheckPlayName(playerName)) {
            std::cout << "Name:" << playerName << " is not correct(uppercase characters only). Please input again." << std::endl;
         }
         // once = true;
      } else {
         return false;
      }
      std::cin.get();
   } while (!CheckPlayName(playerName));
   
   return true;
}
