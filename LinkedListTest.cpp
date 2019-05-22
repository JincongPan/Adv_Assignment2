
#include "LinkedList.h"

#include <iostream>
// <<<<<<< Dekang-Zeng
#include <assert.h>

char colour[] = {'R', 'O', 'Y', 'G', 'B', 'P'};
int shape[] = {1, 2, 3, 4, 5, 6};

// pop null linkedlist 
void PopNullTest() {
   LinkedList* list = new LinkedList();
   Node *node;
   node = list->Pop();
   assert(node == nullptr);
}

void ShuffleTest() {
   LinkedList* list = new LinkedList();
   for (int i = 0; i < 6; ++i) {
      for (int j = 0; j < 6; ++j) {
         Tile* t1 = new Tile(colour[i], shape[j]);
         list->InsertTileToTail(t1);
      }
   }

   std::cout << "Before Shuffle: " << list->GetTiles() << std::endl;
   list->Shuffle();
   std::cout << "After Shuffle:  "<< list->GetTiles() << std::endl;
}

void GetTilesTest() {
   LinkedList* list = new LinkedList();
   std::string tiles = list->GetTiles();
   std::cout << "Null linkedlist: " << tiles << std::endl;
}

void InsertDeleteTest() {
   LinkedList* list = new LinkedList();
   Tile* t1 = new Tile('R', 6);
   assert(list->HasTile(t1) == false);

   list->InsertTileToTail(t1);
   assert(list->HasTile(t1) == true);

   Node* td = list->DeleteTile(t1);
   std::cout << "DeleteTile: " << td->tile->colour << td->tile->shape << std::endl;
   assert(list->HasTile(t1) == false);
}

void BagTest() {
   LinkedList* list = new LinkedList();
=======
char colour[] = {'R', 'O', 'Y', 'G', 'B', 'P'};
int shape[] = {1, 2, 3, 4, 5, 6};

int main(void) {
   LinkedList* list = new LinkedList();

// >>>>>>> master
   for (int i = 0; i < 6; ++i) {
      for (int j = 0; j < 6; ++j) {
         // std::cout << i << " " << j << std::endl;
         Tile* t1 = new Tile(colour[i], shape[j]);
// <<<<<<< Dekang-Zeng
         list->InsertTileToTail(t1);
=======
         list->InsertNodeToTail(t1);
// >>>>>>> master
      }
   }

   std::cout << list->GetTiles() << std::endl;
// <<<<<<< Dekang-Zeng
   list->Shuffle();
   std::cout << list->GetTiles() << std::endl;
=======
   // list->PrintTiles();
   list->Shuffle();
   std::cout << list->GetTiles() << std::endl;
   // list->PrintTiles();
// >>>>>>> master
   Node* tn = nullptr;
   
   LinkedList* hand = new LinkedList();
   for (size_t k = 0; k < 6; ++k) {
      tn = list->Pop();
      hand->InsertNodeToTail(tn);
   }
   std::cout << "Before Delete B5, hand's" << hand->GetTiles() << std::endl;
   std::cout << "Before Delete B5, bags's" << list->GetTiles() << std::endl;
   std::cout << "Delete B5" << std::endl;

   // delete B5
   tn = hand->DeleteTile(new Tile('P', 6));
   list->InsertNodeToTail(tn);
   tn = list->Pop();
   hand->InsertNodeToTail(tn);
   std::cout << "After Delete B5, hand's" << hand->GetTiles() << std::endl;
   std::cout << "After Delete B5, bag's" << list->GetTiles() << std::endl;
// <<<<<<< Dekang-Zeng
}

int main(void) {
   PopNullTest();
   ShuffleTest();
   GetTilesTest();
   InsertDeleteTest();
   BagTest();

=======

   // hand->PrintTiles();
// >>>>>>> master
   return 0;
}
