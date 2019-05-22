
#include "LinkedList.h"

#include <random>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>      // std::ostringstream


LinkedList::LinkedList() {
   head = nullptr;
   // next = nullptr;
   tail = nullptr;
   len = 0;
}

// get the linkedlist head node 
Node* LinkedList::Pop() {
   Node* node = head;
   
   if (len >= 2) {
      head = head->next;
   } else if (len == 1) {
      head = nullptr;
      tail = nullptr;
   }

   if (len != 0) {
      if (node->next) {
         node->next = nullptr;
      }

      len--;
   }
   
   return node;
}

void LinkedList::InsertTileToTail(Tile* tile) {
   Node* node = new Node(tile, nullptr);
   InsertNodeToTail(node);
}

void LinkedList::InsertNodeToTail(Node* node) {
   if (head) {
      tail->next = node;
      tail = node;
   } else {
      head = node;
      tail = node;
   }
   len++;
}

std::string LinkedList::GetTiles(bool console, bool unicode) {
   std::ostringstream stream;
   Node* node = head;
   while (node != nullptr) {
      if (console) {
         if (unicode) {
            stream << colourMap.at((node->tile->colour)) << unicodeMap[node->tile->shape] << "(" << node->tile->colour << node->tile->shape << ")" << colourMap.at('W');
         } else {
            stream << colourMap.at((node->tile->colour)) << node->tile->colour << node->tile->shape << colourMap.at('W');
         }
      } else {
         stream << node->tile->colour << node->tile->shape;
      }
      
      node = node->next;
      if (node) {
         stream << ",";
      }
   }
   // stream << std::endl;

   return stream.str();
}

bool LinkedList::HasTile(Tile* tile) {
   Node* node = head;
   while (node != nullptr) {
      if ((node->tile->colour == tile->colour) && (node->tile->shape == tile->shape)) {
         return true;
      }
      node = node->next;
   }
   return false;
}

Node* LinkedList::DeleteTile(Tile* tile) {
   Node* node = head;
   Node* prev = nullptr;

   while (node != nullptr) {
      if ((node->tile->colour == tile->colour) && (node->tile->shape == tile->shape)) {
         if (prev) {
            prev->next = prev->next->next;
            if (node == tail) {
               tail = prev;
            }
         } else {
            head = head->next;
         }
         len--;
         node->next = nullptr;
         return node;
      }
      prev = node;
      node = node->next;
   }
   return nullptr;
}

// using std::shuffle to shuffle the linkedlist 
void LinkedList::Shuffle() {
   std::vector<Node*> nodes;
   Node* node = head;
   size_t num = 0, i;
   std::random_device rd;
   std::mt19937 gen(rd());

   // put the linkedlist's nodes in vector then using shuffle
   while (node != nullptr) {
      nodes.push_back(node);
      node = node->next;
   }

   std::shuffle(nodes.begin(), nodes.end(), gen);
   num = nodes.size();
   
   // reestablishment the linkedlist 
   Node* prev = nullptr;
   i = num;
   while (i > 0) {
      nodes[i - 1]->next = prev;
      prev = nodes[i - 1];
      i--;
   }

   tail = nodes[num - 1];
   tail->next = nullptr;
   head = nodes[0];
}

LinkedList::~LinkedList() {
   Node* node;
   while (head != nullptr) {
      node = head;
      head = head->next;
      delete node;
   }

   tail = nullptr;
   len = 0;
}
