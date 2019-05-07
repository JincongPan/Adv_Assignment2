#ifndef ASSIGN2_IO_H
#define ASSIGN2_IO_H

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream
#include <unordered_map>

std::string DisplayBoard();
void DisplayGame(int id);
void PrintMenuMessage();
void PrintHelpMessage();
void PrintStudentInformation();
void InputGamePath(std::string &path);
bool LoadGame(std::string path, int &start);
bool SaveGame(std::string path, int id);
void InputPlayerName(std::string &playerName, int id);
#endif // ASSIGN2_IO_H
