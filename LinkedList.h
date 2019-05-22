
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "CheckFormat.h"
#include <iostream>

class LinkedList {
public:
   LinkedList();
   ~LinkedList();

   void InsertTileToTail(Tile* tile);
   void InsertNodeToTail(Node* node);
   std::string GetTiles(bool console, bool unicode);
   bool HasTile(Tile* tile);
   // remove the first node of the same color and shape as the tile from the linkedlist
   Node* DeleteTile(Tile* tile);
   void Shuffle();
   // pop the first node of the linkedlist
   Node* Pop();
private:
   Node* head;
   Node* tail;
   unsigned long len;
};

#endif // ASSIGN2_LINKEDLIST_H
