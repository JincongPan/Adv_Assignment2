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
LinkedList* listBag;
// save player’s name
std::vector<std::string> playerNames;
// save the player hand’s tiles. The member variable of the vector is a pointer to the linkedlist.
std::vector<LinkedList*> playerHands;
// save player’s scores
std::vector<size_t> playerScores;
// a 2D array of 26X26, saves the tiles of the board
std::vector<std::vector<Tile*>> board(ROW, std::vector<Tile*>(COLUMN, new Tile(' ', -1)));
std::priority_queue<Score> highScores;          // record highscores
std::unordered_map<char, std::string> colourMap = {
         {'R', "\033[0;31m"},                        /* Red */
         {'G', "\033[0;32m"},                        /* Green */
         {'Y', "\033[0;33m"},                        /* Yellow */
         {'B', "\033[0;34m"},                        /* Blue */
         {'W', "\033[0;37m"},                        /* White */
         {'P', "\033[0;35m"},                        /* Purple */
         {'O', "\033[1;31m"}                         /* Orange */
};

std::unordered_map<int, std::string> unicodeMap = {
         {1, "\u25CF"},                        /* Circle */
         {2, "\u2726"},                        /* 4-Star */
         {3, "\u25C6"},                        /* Diamond */
         {4, "\u25A0"},                        /* Square */
         {5, "\u2736"},                        /* 6-Star */
         {6, "\u2724"},                        /* Clover */
};
bool restart = true;
bool unicode = false;
bool initialization = false;

void PrintChar() {
   std::cin.clear();
   std::cout << "> ";
}

// compare function for priority queue 
bool operator<(const Score& s1, const Score& s2) { 
   return s1.score < s2.score;
}

int HasSameColourLevel(int row, int col, Tile* tp) {
   int same = 1;
   // level check if has same colour 
   for (int i = col + 1; i < COLUMN; ++i) {
      if (board[row][i]->colour == ' ') {
         break;
      } else if (board[row][i]->colour == tp->colour) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   for (int i = col - 1; i >= 0; --i) {
      if (board[row][i]->colour == ' ') {
         break;
      } else if (board[row][i]->colour == tp->colour) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   return same;
}

int HasSameColourVertical(int row, int col, Tile* tp) {
   int same = 1;
   // vertical check if has same attribute 
   for (int i = row + 1; i < ROW; ++i) {
      if (board[i][col]->colour == ' ') {
         break;
      } else if (board[i][col]->colour == tp->colour) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   for (int i = row - 1; i >= 0; --i) {
      if (board[i][col]->colour == ' ') {
         break;
      } else if (board[i][col]->colour == tp->colour) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   return same;
}

// 0:different  1:null  2:same
int HasSameShapeLevel(int row, int col, Tile* tp) {
   int same = 1;

   // level check if has same colour 
   for (int i = col + 1; i < COLUMN; ++i) {
      if (board[row][i]->colour == ' ') {
         break;
      } else if (board[row][i]->shape == tp->shape) {
         same = 2;
         continue;
      } else {
         // same = 0;
         return 0;
      }
   }

   for (int i = col - 1; i >= 0; --i) {
      if (board[row][i]->colour == ' ') {
         break;
      } else if (board[row][i]->shape == tp->shape) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   return same;
}

int HasSameShapeVertical(int row, int col, Tile* tp) {
   int same = 1;

   // vertical check if has same attribute 
   for (int i = row + 1; i < ROW; ++i) {
      if (board[i][col]->colour == ' ') {
         break;
      } else if (board[i][col]->shape == tp->shape) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   for (int i = row - 1; i >= 0; --i) {
      if (board[i][col]->colour == ' ') {
         break;
      } else if (board[i][col]->shape == tp->shape) {
         same = 2;
         continue;
      } else {
         return 0;
      }
   }

   return same;
}

bool HasSameTile(int row, int col, Tile* tp) {
   // level check if has same attribute 
   for (int i = col + 1; i < COLUMN; ++i) {
      // ' ' is blank tile 
      // std::cout << "i: " << i << std::endl;
      if (board[row][i]->colour == ' ') {
         break;
      } else {
         if ((board[row][i]->colour == tp->colour) && (board[row][i]->shape == tp->shape)) {
            return true;
         }
      }
   }

   for (int i = col - 1; i >= 0; --i) {
      // ' ' is blank tile 
      // std::cout << "i: " << i << std::endl;
      if (board[row][i]->colour == ' ') {
         break;
      } else {
         if ((board[row][i]->colour == tp->colour) && (board[row][i]->shape == tp->shape)) {
            return true;
         }
      }
   }

   // vertical check if has same attribute 
   for (int i = row + 1; i < ROW; ++i) {
      if (board[i][col]->colour == ' ') {
         break;
      } else {
         if ((board[i][col]->colour == tp->colour) && (board[i][col]->shape == tp->shape)) {
            return true;
         }
      }
   }

   for (int i = row - 1; i >= 0; --i) {
      if (board[i][col]->colour == ' ') {
         break;
      } else {
         if ((board[i][col]->colour == tp->colour) && (board[i][col]->shape == tp->shape)) {
            return true;
         }
      }
   }

   return false;
}

// qwirkle rules 
bool QwirkleRulesCheck(int row, int col, Tile* tp) {
   bool allowed = true;

   if (board[row][col]->colour != ' ') return false;
   
   // not allowed the line has the same tile 
   if (HasSameTile(row, col, tp)) {
      allowed = false;
   } else {
      // level line has no tiles
      if (!initialization) {
         allowed = true;
      } else {
         if (HasSameColourLevel(row, col, tp) == 1) {
            if ((HasSameColourVertical(row, col, tp) == 2) || (HasSameShapeVertical(row, col, tp) == 2)) {
               allowed = true;
            } else {
               allowed = false;
            }
         // vertical line has no tiles
         } else if (HasSameColourVertical(row, col, tp) == 1) {
            if ((HasSameColourLevel(row, col, tp) == 2) || (HasSameShapeLevel(row, col, tp) == 2)) {
               allowed = true;
            } else {
               allowed = false;
            }
         } else {
            if ((HasSameColourLevel(row, col, tp) == 0) && (HasSameShapeLevel(row, col, tp) == 0)) {
               allowed = false;
            } else if ((HasSameColourVertical(row, col, tp) == 0) && (HasSameShapeVertical(row, col, tp) == 0)) {
               allowed = false;
            } else {
               allowed = true;
            }
         }
      }

      // if (HasSameColourLevel(row, col, tp) == 1) {
      //    if ((HasSameColourVertical(row, col, tp) == 0) && (HasSameShapeVertical(row, col, tp) == 0)) {
      //       allowed = false;
      //    } else {
      //       allowed = true;
      //    }
      // // vertical line has no tiles
      // } else if (HasSameColourVertical(row, col, tp) == 1) {
      //    if ((HasSameColourLevel(row, col, tp) == 0) && (HasSameShapeLevel(row, col, tp) == 0)) {
      //       allowed = false;
      //    } else {
      //       allowed = true;
      //    }
      // } else {
      //   // level line or vertical line has the same attribute
      //   if (HasSameColourLevel(row, col, tp) == 2) {
      //      allowed = true;
      //   } else if (HasSameShapeLevel(row, col, tp) == 2) {
      //      allowed = true;
      //   } else if (HasSameColourVertical(row, col, tp) == 2) {
      //      allowed = true;
      //   } else if (HasSameShapeVertical(row, col, tp) == 2) {
      //      allowed = true;
      //   } else {
      //      allowed = false;
      //   }
      // }
   }
   
   initialization = true;
   return allowed;
}

// increase score, return value show if qwirkle!!!
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
   for (int i = col + 1; i < COLUMN; ++i) {
      if (board[row][i]->colour == tp->colour) {
         cls++;
      } else {
         break;
      }
   }
   for (int i = col - 1; i >= 0; --i) {
      if (board[row][i]->colour == tp->colour) {
         cls++;
      } else {
         break;
      }
   }

   // colour vertical
   int cvs = 1;
   for (int i = row + 1; i < ROW; ++i) {
      if (board[i][col]->colour == tp->colour) {
         cvs++;
      } else {
         break;
      }
   }
   for (int i = row - 1; i >= 0; --i) {
      if (board[i][col]->colour == tp->colour) {
         cvs++;
      } else {
         break;
      }
   }

   // shape level
   int tls = 1;
   for (int i = col + 1; i < COLUMN; ++i) {
      if (board[row][i]->shape == tp->shape) {
         tls++;
      } else {
         break;
      }
   }
   for (int i = col - 1; i >= 0; --i) {
      if (board[row][i]->shape == tp->shape) {
         tls++;
      } else {
         break;
      }
   }

   // shape vertical
   int tvs = 1;
   for (int i = row + 1; i < ROW; ++i) {
      if (board[i][col]->shape == tp->shape) {
         tvs++;
      } else {
         break;
      }
   }
   for (int i = row - 1; i >= 0; --i) {
      if (board[i][col]->shape == tp->shape) {
         tvs++;
      } else {
         break;
      }
   }

   // std::cout << "cls: " << cls << "cvs: " << cvs << "tvs: " << tvs << "tls: " << tls << std::endl;
   int maxl = std::max(cls, tls);
   int maxt = std::max(tvs, cvs);

   maxl = (maxl > 1) ? maxl : 0;
   maxt = (maxt > 1) ? maxt : 0;

   // if qwirkle, the score becomes double 
   if (maxl == 6) {
      qwirkle = true; 
      maxl = maxl * 2;
   }

   if (maxt == 6) {
      qwirkle = true; 
      maxt = maxt * 2;
   }
   // std::cout << "maxl: " << maxl << "maxt: " << maxt << std::endl;
   score = maxl + maxt;
   return qwirkle;
}

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
                  std::cout << "Tile:" << tile << " is error. Please input action command again." << std::endl;
                  PrintChar();
                  continue;
               }
               if (!playerHands[i]->HasTile(tp) || (at.compare("at") != 0)) {
                  std::cout << "Player's hand doesn't have " << tile << ". Please input action command again."<< std::endl;
                  PrintChar();
                  continue;
               }
               if (!CheckLocation(location, row, col)) {
                  // std::cout << "Location error. format: <row><column>" << tile << row + 'A' << " " << col << std::endl;
                  std::cout << "Location:" << char(row + 'A') << col << " is error. Please input action command again." << std::endl;
                  PrintChar();
                  continue;
               }

               // qwirkle rule check
               if (QwirkleRulesCheck(row, col, tp)) {
                  // increase scores 
                  int score;
                  if (IncScore(row, col, tp, score)) {
                     std::cout << "QWIRKLE!!!" << std::endl;
                  }
                  playerScores[i] += score;

                  inputCorrect = true;
                  board[row][col] = tp;
                  playerHands[i]->DeleteTile(tp);
                  Node* node = listBag->Pop();
                  if (node) {
                     playerHands[i]->InsertNodeToTail(node);
                  } else {
                     std::cout << "Bag is empty" << std::endl;
                  }
                  
                  // std::cout << "place action: " << tp->colour << tp->shape << " " << char(row + 'A') << col << std::endl;
               } else {
                  std::cout << "place " << tp->colour << tp->shape << " at " << char(row + 'A') << col << " is not allowed in qwirkle rules. Please input action command again." << std::endl;
                  PrintChar();
                  continue;
               }
            // replace command
            } else if (action.compare("replace") == 0) {
               std::string tile;
               std::cin >> tile;
               std::cout << "player " << playerNames[i] << " replace " << tile << ", it's hand tiles: " << playerHands[i]->GetTiles(true, unicode) << std::endl;
               
               Tile* tp = nullptr; 
               if (!(tp = CheckTile(tile))) {
                  std::cout << "Tile:" << tile << " is error. Please input action command again." << std::endl;
                  PrintChar();
                  continue;
               }

               Node* node = playerHands[i]->DeleteTile(tp);
               if (node == nullptr) {
                  std::cout << "Player's hand doesn't have " << tile << ". Please input action command again."<< std::endl;
                  inputCorrect = false;
               } else {
                  std::cout << "bags: " << listBag->GetTiles(true, unicode) << std::endl;
                  listBag->InsertNodeToTail(node);
                  node = listBag->Pop();
                  if (node) {
                     playerHands[i]->InsertNodeToTail(node);
                  } else {
                     std::cout << "Bag is empty" << std::endl;
                  }
                  
                  inputCorrect = true;
                  std::cout << "player " << playerNames[i] << " after replace " << tile << " hand's: " << playerHands[i]->GetTiles(true, unicode) << std::endl;
                  std::cout << "bags: " << listBag->GetTiles(true, unicode) << std::endl;
               }

            // save command
            } else if (action.compare("save") == 0) {
               std::string filename;
               std::cin >> filename;
               if (SaveGame(filename, i)) {
                  std::cout << "Game successfully saved" << std::endl;
               } else {
                  std::cout << "Game saved failed" << std::endl;
               }
               PrintChar();
            // help command
            } else if (action.compare("help") == 0) {
               PrintHelpMessage();
               std::cout << "> ";
            } else if (action.compare("quit") == 0) {
               return;
            } else if (action.compare("restart") == 0) {
               restart = true;
               return ; // restart
            } else if (action.compare("highscore") == 0) {
               PrintHighScores();
            } else {
               std::cout << "Action is error, place input again" << std::endl;
               DisplayGame(i);
               PrintChar();
            }
         }

         // EOF for quit
         if (!inputCorrect) {
            std::cout << "EOF input end." << std::endl;
            running = false;
            break;
            // exit(EXIT_SUCCESS);
         }

         // whether end the game, just only 1. The tile bag is empty && 2. One player has no more tiles in their hand
         if (playerHands[i] == NULL) {
            PrintGameOverInformation();
         }

      }
   }
}

bool InitGame() {
   // init bag    
   // there are only 2 tiles of each type
   std::string playerNumString;
   do {
      std::cout << "Please input the playerNum(2, 3, 4): ";
      if (std::cin >> playerNumString) {
         try {
            playerNum = std::stoi(playerNumString);
         } catch (const std::invalid_argument& iat) {
            playerNum = 0;
         }
         std::cin.get();
      } else {
         return false;
      }
      
      // std::cout << "Player: " << playerNum << std::endl;
      if ((playerNum > 4) || (playerNum < 2)) {
         std::cout << "playerNum:" << playerNumString << " error, only support 2, 3 or 4" << std::endl;
      }
   } while ((playerNum > 4) || (playerNum < 2));

   listBag = new LinkedList();
   for (size_t i = 0; i < COLOUR_SIZE; ++i) {
      for (size_t j = 0; j < SHAPE_SIZE; ++j) {
         // 
         Tile* t1 = new Tile(colour[i], shape[j]);
         Tile* t2 = new Tile(colour[i], shape[j]);
         listBag->InsertTileToTail(t1);
         listBag->InsertTileToTail(t2);
         if (playerNum > 2) {
            Tile* t3 = new Tile(colour[i], shape[j]);
            listBag->InsertTileToTail(t3);
         }
      }
   }
   // shuffle the bag's tiles
   listBag->Shuffle();

   // init player name and it's hand's tiles
   std::cout << std::endl << "Starting a New Game" << std::endl;
   Node* t = nullptr;
   playerNames.clear();
   playerHands.clear();
   playerScores.clear();
   initialization = false;
   std::vector<std::vector<Tile*>> board_t(ROW, std::vector<Tile*>(COLUMN, new Tile(' ', -1)));
   board.swap(board_t);
   while (!highScores.empty()) {
      highScores.pop();
   }

   for (size_t i = 0; i < playerNum; ++i) {
      std::string playerName;
      
      if (!InputPlayerName(playerName, i+1)) {
         return false;
      }
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

   return true;
}

void ClearGame() {
   listBag = new LinkedList();
   playerNames.clear();
   playerHands.clear();
   playerScores.clear();
   initialization = false;
   std::vector<std::vector<Tile*>> board_t(ROW, std::vector<Tile*>(COLUMN, new Tile(' ', -1)));
   board.swap(board_t);
   while (!highScores.empty()) {
      highScores.pop();
   }
}

void RunningGame() {
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
               if (InitGame()) {
                  PlayGame(0);
               }
               
               invalidInput = false;
               break;
            case 2:
               ClearGame();
               InputGamePath(path);
               if (LoadGame(path, start)) {
                  std::cout << "Qwirkle game successfully loaded" << std::endl;
                  // std::cout << "Start: " << start << std::endl;
                  PlayGame(start);
                  invalidInput = false;
               } else {
                  std::cout << "Qwirkle game loaded failed" << std::endl;
                  invalidInput = true;
               }
               break;
            case 3:
               PrintStudentInformation();
               PrintMenuMessage();
               std::cout << "> ";
               break;
            case 4:
               invalidInput = false;
               break;
            default:
               std::cout << "Invalid Input, please input the correct num(1, 2, 3, 4)." << std::endl;
               std::cout << "> ";
         }
         
      } catch (const std::invalid_argument& iat) {
         std::cout << "Invalid Input, please input the correct num(1, 2, 3, 4)." << std::endl;
         std::cout << "> "; 
      }
   }
}

int main(void) {

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   while (restart) {
      restart = false;
      RunningGame();
   }
   
   std::cout << "Goodbye" << std::endl; 

   return EXIT_SUCCESS;
}
