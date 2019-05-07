#include "LinkedList.h"
#include "IO.h"
#include "CheckFormat.h"
#include "qwirkle.h"

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream
#include <queue>          // std::priority_queue

// global variable, shared between qwirkle.cpp IO.cpp
char colour[] = {'R', 'O', 'Y', 'G', 'B', 'P'};
int shape[] = {1, 2, 3, 4, 5, 6};
size_t playerNum;       // player's number 2,3,4...
std::vector<std::string> playerNames;
std::vector<LinkedList*> playerHands;
std::vector<size_t> playerScores;
LinkedList* listBag;
std::vector<std::vector<Tile*>> board(ROW, std::vector<Tile*>(COLUMN, new Tile(' ', -1)));
std::priority_queue<Score> highScores;          // record highscores
std::unordered_map<char, std::string> colourMap = {
         {'R', "\033[31m"},                        /* Red */
         {'G', "\033[32m"},                        /* Green */
         {'Y', "\033[33m"},                        /* Yellow */
         {'B', "\033[34m"},                        /* Blue */
         {'W', "\033[37m"},                        /* White */
         {'P', "\033[35m"},                        /* Purple */
         {'O', "\033[34m"}                         /* Orange */
};

void PrintChar() {
   std::cin.clear();
   std::cout << "> ";
}

// compare function for priority queue 
bool operator<(const Score& s1, const Score& s2) { 
   return s1.score < s2.score;
}

// qwirkle rules 
bool IncScore(int row, int col, Tile* tp, int& score) {
   bool qwirkle = false;
   std::unordered_map<char, int> mp = {
      {'R', 0},
      {'O', 0},
      {'Y', 0},
      {'G', 0},
      {'B', 0},
      {'P', 0},
   };
   // colour level
   int cls = 1;
   for (size_t i = col; i < COLUMN; ++i) {
      if (board[row][i]->colour == tp->colour) {
         cls++;
      } else {
         break;
      }
   }
   for (size_t i = col; i >= 0; --i) {
      if (board[row][i]->colour == tp->colour) {
         cls++;
      } else {
         break;
      }
   }

   // colour vertical
   int cvs = 1;
   for (size_t i = row; i < ROW; ++i) {
      if (board[i][col]->colour == tp->colour) {
         cvs++;
      } else {
         break;
      }
   }
   for (size_t i = row; i >= 0; --i) {
      if (board[i][col]->colour == tp->colour) {
         cvs++;
      } else {
         break;
      }
   }

   // shape level
   int tls = 1;
   for (size_t i = col; i < COLUMN; ++i) {
      if (board[row][i]->shape == tp->shape) {
         tls++;
      } else {
         break;
      }
   }
   for (size_t i = col; i >= 0; --i) {
      if (board[row][i]->shape == tp->shape) {
         tls++;
      } else {
         break;
      }
   }

   // shape vertical
   int tvs = 1;
   for (size_t i = row; i < ROW; ++i) {
      if (board[i][col]->shape == tp->shape) {
         tvs++;
      } else {
         break;
      }
   }
   for (size_t i = row; i >= 0; --i) {
      if (board[i][col]->shape == tp->shape) {
         tvs++;
      } else {
         break;
      }
   }

   int maxl = std::max(cls, cvs);
   int maxt = std::max(tvs, tls);

   maxl = (maxl > 1) ? maxl : 0;
   maxt = (maxt > 1) ? maxt : 0;

   if ((maxl == 6) || (maxt == 6)) {
      qwirkle = true;
   }
   score = maxl + maxt;
   return qwirkle;
}

// 
// start is the current player 
void PlayGame(int start) {
   std::string action;
   bool running = true;
   while (running) {
      for (size_t i = start; i < playerNum; ++i) {
         DisplayGame(i);
         bool inputCorrect = false;
         std::cout << "> ";
         while((!inputCorrect) && (std::cin >> action)) {
            // execute the following actions : place, replace, save,  help

            if (action.compare("place") == 0) {
               std::string tile, at, location;
               std::cin >> tile >> at >> location;
               std::cout << "place action: " << tile << " " << at << " " << location << std::endl;
               Tile* tp = nullptr; 
               int col, row;

               if (!(tp = CheckTile(tile))) {
                  std::cout << "Tile Format error." << tile << std::endl;
                  PrintChar();
                  continue;
               }
               if (!playerHands[i]->HasTile(tp) || (at.compare("at") != 0)) {
                  std::cout << "Player's hand doesn't have" << tile << std::endl;
                  PrintChar();
                  continue;
               }
               if (!CheckLocation(location, row, col)) {
                  std::cout << "Location error. format: <row><column>" << tile << row << " " << col << std::endl;
                  PrintChar();
                  continue;
               }

               // qwirkle rule check
               int score;
               if (IncScore(row, col, tp, score)) {
                  std::cout << "QWIRKLE!!!" << std::endl;
               }
               playerScores[i] += score;

               inputCorrect = true;
               board[row][col] = tp;
               Node* node = listBag->Pop();
               playerHands[i]->InsertNodeToTail(node);
               std::cout << "place action: " << tp->colour << tp->shape << " " << row << " " << col << std::endl;
            
            // replace command
            } else if (action.compare("replace") == 0) {
               std::string tile;
               std::cin >> tile;
               std::cout << "player " << playerNames[i] << " replace " << tile << " hand's: " << playerHands[i]->GetTiles() << std::endl;
               std::cout << "bags: " << listBag->GetTiles() << std::endl;
               
               Tile* tp = nullptr; 
               if (!(tp = CheckTile(tile))) {
                  std::cout << "Tile Format error. Tile contains: <colour><shape>" << tile << std::endl;
                  PrintChar();
                  continue;
               }

               Node* node = playerHands[i]->DeleteTile(tp);
               if (node == nullptr) {
                  std::cout << "player hand doesn't have " << tile << std::endl;
                  inputCorrect = false;
               } else {
                  listBag->InsertNodeToTail(node);
                  node = listBag->Pop();
                  playerHands[i]->InsertNodeToTail(node);
                  inputCorrect = true;
               }

               std::cout << "player " << playerNames[i] << " after replace " << tile << " hand's: " << playerHands[i]->GetTiles() << std::endl;
               std::cout << "bags: " << listBag->GetTiles() << std::endl;
            
            // save command
            } else if (action.compare("save") == 0) {
               std::string filename;
               std::cin >> filename;
               if (SaveGame(filename, i)) {
                  std::cout << "Game successfully saved" << std::endl;
               } else {
                  std::cout << "Game saved failed" << std::endl;
               }

            // help command
            } else if (action.compare("help") == 0) {
               PrintHelpMessage();
               std::cout << "> ";
            }
         }

         // EOF for quit
         if (!inputCorrect) {
            std::cout << "EOF input end." << std::endl;
            running = false;
            break;
            // exit(EXIT_SUCCESS);
         }
      }
   }
}

void InitGame() {
   // init bag    
   // there are only 2 tiles of each type
   listBag = new LinkedList();
   for (size_t i = 0; i < COLOUR_SIZE; ++i) {
      for (size_t j = 0; j < SHAPE_SIZE; ++j) {
         // 
         Tile* t1 = new Tile(colour[i], shape[j]);
         Tile* t2 = new Tile(colour[i], shape[j]);
         listBag->InsertNodeToTail(t1);
         listBag->InsertNodeToTail(t2);
      }
   }
   // shuffle the bag's tiles
   listBag->Shuffle();

   // init player name and it's hand's tiles
   std::cout << std::endl << "Starting a New Game" << std::endl;
   Node* t = nullptr;
   for (size_t i = 0; i < playerNum; ++i) {
      std::string playerName;
      
      InputPlayerName(playerName, i+1);
      playerNames.push_back(playerName);

      LinkedList* list = new LinkedList();
      for (size_t k = 0; k < HAND_TILE; ++k) {
         t = listBag->Pop();
         list->InsertNodeToTail(t);
      }
      playerHands.push_back(list);
   }

   // init scores
   playerScores.resize(playerNum, 0);
   std::cout << "Let’s Play!" << std::endl;
}

int main(void) {

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   
   PrintMenuMessage();
   std::cout << "> "; 
   
   std::string line;
   bool invalidInput = true;
   std::string path;
   playerNum = 2;    // player's number can be config
   while (invalidInput && (std::cin >> line)) {
      try {
         int opt = std::stoi(line);
         int start = 0;
         // std::cout << opt << std::endl;
         switch(opt) {
            case 1: 
               InitGame();
               PlayGame(0);
               invalidInput = false;
               break;
            case 2:
               InputGamePath(path);
               if (LoadGame(path, start)) {
                  std::cout << "Qwirkle game successfully loaded" << std::endl;
                  PlayGame(start);
                  invalidInput = false;
               } else {
                  std::cout << "Qwirkle game loaded failed" << std::endl;
                  invalidInput = true;
               }
               break;
            case 3:
               PrintStudentInformation();
               std::cout << "> ";
               break;
            case 4:
               invalidInput = false;
               break;
            default:
               std::cout << "Invalid Input" << std::endl;
               std::cout << "> ";
         }
         
      } catch (const std::invalid_argument& iat) {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> "; 
      }
      
   }
   std::cout << "Goodbye" << std::endl; 

   return EXIT_SUCCESS;
}
