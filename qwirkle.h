
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
extern std::unordered_map<int, std::string> unicodeMap;
extern std::priority_queue<Score> highScores;
extern bool restart;
extern bool unicode;

extern bool operator<(const Score& s1, const Score& s2);	// compare function 

// qwirkle rules check 
int HasSameColourLevel(int row, int col, Tile* tp);
int HasSameColourVertical(int row, int col, Tile* tp);
int HasSameShapeLevel(int row, int col, Tile* tp);
int HasSameShapeVertical(int row, int col, Tile* tp);
bool HasSameTile(int row, int col, Tile* tp);
// Checks whether the placed tiles conform to the rules of the game.
// The locations where Tiles are placed must have the same properties, but they may not be adjacent.
bool QwirkleRulesCheck(int row, int col, Tile* tp);
// The user's score is updated after the user places the tile. When counting scores, the level 
//  and top and bottom statistics of the adjacent tiles with the same attribute have, and 
//  return the score that should be increased
bool IncScore(int row, int col, Tile* tp, int& score);

// game execution to parse the user's actions
void PlayGame(int start);
// initialize the qwirkle game, first initialize the bag, then shuffle. 
//  The player's name, score, hand, etc. are then initialized
bool InitGame();
void ClearGame();
// run the entire qwirkle program, first output menu options
void RunningGame();
#endif // ASSIGN2_QWIRKLE_H
