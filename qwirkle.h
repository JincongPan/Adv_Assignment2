
#ifndef ASSIGN2_QWIRKLE_H
#define ASSIGN2_QWIRKLE_H
#include "LinkedList.h"
#include "IO.h"
#include "CheckFormat.h"

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream
#include <queue>

#define EXIT_SUCCESS    0
#define COLOUR_SIZE     6
#define SHAPE_SIZE      6
#define ROW             26
#define COLUMN          26
#define HAND_TILE       6

class LinkedList;
class Score {
  public:
	std::string name;
	int score;
	Score(std::string n, int s) {
		name = n;
		score = s;
	}
};

extern size_t playerNum;
extern std::vector<std::string> playerNames;
extern std::vector<LinkedList*> playerHands;
extern std::vector<size_t> playerScores;
extern LinkedList* listBag;
extern std::vector<std::vector<Tile*>> board;
extern char colour[];
extern int shape[];
extern std::unordered_map<char, std::string> colourMap;
extern std::priority_queue<Score> highScores;

extern bool operator<(const Score& s1, const Score& s2);	// compare function 
#endif // ASSIGN2_QWIRKLE_H
