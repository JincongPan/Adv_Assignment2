#ifndef ASSIGN2_IO_H
#define ASSIGN2_IO_H

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream
#include <unordered_map>

// Save the board information to string.The function distinguishes whether to output to the console. 
// When the board information is to be output to the console, the colorMap is used to color the pieces; 
//  if the board information is saved to the file, there is no color information.
std::string DisplayBoard(bool console);
// Save the board information in unicode to string.
std::string DisplayBoardUnicode();
// Outputs the current state of the game, such as the current playername, hand, current score, etc.
void DisplayGame(int id);
// Outputs menu information
void PrintMenuMessage();
// Output help auxiliary information, some operation instructions that can be input
void PrintHelpMessage();
// Output student information
void PrintStudentInformation();
// Outputs the player's score and winner at the end of the game
void PrintGameOverInformation();
void InputGamePath(std::string &path);
/* Loads the game from the file in the path path, and start indicates the current player number. 
    Mainly design player name, score, hand analysis, initialization */
bool LoadGame(std::string path, int &start);
// Saves the current game information to the path file
bool SaveGame(std::string path, int id);
bool InputPlayerName(std::string &playerName, int id);
void PrintHighScores();
#endif // ASSIGN2_IO_H
