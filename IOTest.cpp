#include "LinkedList.h"
#include "qwirkle.h"

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream

char colour[] = {'R', 'O', 'Y', 'G', 'B', 'P'};
int shape[] = {1, 2, 3, 4, 5, 6};
size_t playerNum;
std::vector<std::string> playerNames;
std::vector<LinkedList*> playerHands;
std::vector<size_t> playerScores;
LinkedList* listBag;
std::vector<std::vector<Tile*>> board(ROW, std::vector<Tile*>(COLUMN, new Tile(' ', -1)));
std::priority_queue<Score> highScores;
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
         {1, "\u25CB"},                        /* Circle */
         {2, "\u2726"},                        /* 4-Star */
         {3, "\u29E8"},                        /* Diamond */
         {4, "\u25A1"},                        /* Square */
         {5, "\u2736"},                        /* 6-Star */
         {6, "\u2724"},                        /* Clover */
};
// compare function 
bool operator<(const Score& s1, const Score& s2) {
   return s1.score < s2.score;
}

int main(void) {
    int start;
    std::string str = "\u265E";
    std::cout << str << std::endl;
    LoadGame("./test_load_and_save_game_1.save", start);
   //  std::cout << "Start: " << start << std::endl;
    SaveGame("./test_load_and_save_game_1.actualsave", start);
}
