
#ifndef ASSIGN2_CHECK_FORMAT_H
#define ASSIGN2_CHECK_FORMAT_H
#include "LinkedList.h"
#include "qwirkle.h"

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream

bool CheckPlayName(std::string &name);

Tile* CheckTile(std::string tile);

bool CheckLocation(std::string loc, int &row, int &col);

#endif // ASSIGN2_CHECK_FORMAT_H
