
#ifndef ASSIGN2_CHECK_FORMAT_H
#define ASSIGN2_CHECK_FORMAT_H
#include "LinkedList.h"
#include "qwirkle.h"

#include <iostream>
#include <vector>
#include <fstream>      // std::ofstream
#include <sstream>      // std::ostringstream

bool CheckPlayName(std::string &name) {
   for (size_t i = 0; i < name.size(); ++i) {
      if ((name[i] < 'A') || (name[i] > 'Z')) {
         return false;
      }
   }

   return true;
}

Tile* CheckTile(std::string tile) {
   if (tile.size() != 2) return nullptr;
   char col = tile[0];
   int sha = tile[1] - '0';
   for (size_t i = 0; i < COLOUR_SIZE; ++i) {
      if (col == colour[i]) {
         for (size_t k = 0; k < SHAPE_SIZE; ++k) {
            if (sha == shape[k]) {
               Tile* tp = new Tile(col, sha);
               return tp;
            }
         }
      }
   }
   return nullptr;
}

// bool CheckTileExistHand(LinkedList* hand, Tile* tp) {
//    if (hand->HasTile(tp)) {
//       // std::cout << "true" << std::endl;
//       return true;
//    } else {
//       return false;
//    }
// }

bool CheckLocation(std::string loc, int &row, int &col) {
   // if (loc.size() != 2) return false;
   row = loc[0] - 'A';
   col = 0;
   try {
      col = std::stoi(std::string(loc.begin() + 1, loc.end()));
   } catch (const std::invalid_argument& iat) {
      return false;
   }

   // std::cout << "CheckLocation: " << loc << " " << row << " " << col << std::endl;
   if ((row >= 0) && (row < ROW) && (col > 0) && (col < COLUMN)) {
      if (board[row][col]->shape == -1) {
         return true;
      }
   }

   return false;
}

#endif // ASSIGN2_CHECK_FORMAT_H
